#include <xc.h>
#include "accumulateur.h"
#include "test.h"

/**
 * Bits de configuration:
 */
#pragma config FOSC = INTIO67  // Oscillateur interne, ports A6 et A7 comme IO.
#pragma config IESO = OFF      // Pas d'embrouilles avec l'osc. au démarrage.
#pragma config FCMEN = OFF     // Pas de monitorage de l'oscillateur.

// Nécessaires pour ICSP / ICD:
#pragma config MCLRE = EXTMCLR // RE3 est actif comme master reset.
#pragma config WDTEN = OFF     // Watchdog inactif (pour ICSP /ICD)
#pragma config LVP = OFF       // Single Supply Enable bits off.

#ifndef TEST

/**
 * Configure le circuit selon l'état de l'accumulateur.
 * @param accumulateur L'état de l'accumulateur.
 */
void configureCircuit(Accumulateur *accumulateur) {
    PORTAbits.RA2 = accumulateur->accumulateurDisponible;
    PORTAbits.RA3 = accumulateur->accumulateurEnCharge;
    PORTAbits.RA4 = accumulateur->accumulateurSollicite;    
}

/**
 * Énumère les sources de conversion Analogique/Digital.
 * Intègre le numéro de canal (AN1... AN6) dans l'énumération.
 */
typedef enum {
    ACCUMULATEUR = 0,
    ALIMENTATION = 1
} SourceAD;

/**
 * Gère les interruptions de basse priorité.
 */
void interrupt low_priority bassePriorite() {
    static SourceAD sourceAD = ACCUMULATEUR;
    Accumulateur *accumulateur;
    unsigned char conversion;

    // Lance une conversion Analogique / Digitale:
    if (INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        TMR0H = 0xFF;
        TMR0L = 0x37;

        ADCON0bits.CHS = sourceAD;
        ADCON0bits.GODONE = 1;
    }
    
    // Reçoit le résultat de la conversion Analogique / Digitale.
    if (PIR1bits.ADIF) {
        conversion = ADRESH;
        PIR1bits.ADIF = 0;
        switch (sourceAD) {
            case ACCUMULATEUR:
                accumulateur = mesureAccumulateur(conversion);
                sourceAD = ALIMENTATION;
                break;
                
            case ALIMENTATION:
            default:
                accumulateur = mesureAlimentation(conversion);
                sourceAD = ACCUMULATEUR;
                break;
        }
        configureCircuit(accumulateur);
    }
}

/**
 * Initialise le hardware.
 */
static void hardwareInitialise() {
    // Configure tous les ports comme entrées:
    TRISA = 0b11100011;
    TRISB = 0b11111111;
    TRISC = 0b11111111;
    
    // Configure le micro contrôleur pour 8MHz:
    OSCCONbits.IRCF = 6;    // Fréquence de base: 6 ==> 8 MHz
    OSCTUNEbits.PLLEN = 0;  // Pas de PLL.
    
    // Active le temporisateur 0 pour surveiller les entrées analogiques
    // Période d'interruption: 100uS
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.TMR0ON = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCON2bits.TMR0IP = 0;
    
    // Configure le module A/D:
    ANSELA = 0b00000011; // Active AN0 et AN1 comme entrées analogiques.
    ANSELB = 0b00000000; // Désactive les convertisseurs A/D.
    ANSELC = 0b00000000; // Désactive les convertisseurs A/D.

    ADCON2bits.ADFM = 0; // Résultat justifié sur ADRESH.
    ADCON2bits.ACQT = 5; // Temps d'acquisition: 12 TAD
    ADCON2bits.ADCS = 5; // TAD de 1uS pour FOSC = 8MHz

    ADCON0bits.CHS = 0;  // Canal AN0 (RA0).
    ADCON0bits.ADON = 1; // Active le module A/D.
    
    PIE1bits.ADIE = 1;      // Interruptions du module A/D
    IPR1bits.ADIP = 0;      // Basse priorité.
    
    // Active les interruptions générales:
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

/**
 * Point d'entrée pour l'émetteur de radio contrôle.
 */
void main(void) {
    hardwareInitialise();
    while(1);
}
#endif

#ifdef TEST
void main(void) {
    initialiseTests();
    testeAccumulateur();
    finaliseTests();
    while(1);
}
#endif
