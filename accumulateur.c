#include "accumulateur.h"
#include "test.h"

/**
 * État actuel de l'accumulateur.
 */
Accumulateur accumulateur = {0, 0, 0, 0};

/**
 * Initialise l'état de l'accumulateur.
 */
void initialiseAccumulateur() {
    accumulateur.accumulateurDisponible = 0;
    accumulateur.accumulateurEnCharge = 0;
    accumulateur.accumulateurPresent = 0;
    accumulateur.accumulateurSollicite = 0;
}

/**
 * Actualise l'état de l'accumulateur par rapport à la
 * tension de l'alimentation.
 * @param valim Tension d'alimentation, entre 0 et 255.
 * @return L'état actualisé de l'accumulateur.
 */
Accumulateur *mesureAlimentation(unsigned char valim) {
    // À faire... L'exemple ci-dessous n'est pas fonctionnel.
    if (valim < 127) {
        accumulateur.accumulateurSollicite = 1;
    } else {
        accumulateur.accumulateurSollicite = 0;        
    }
    
    return &accumulateur;
}

Accumulateur *mesureAccumulateur(unsigned char vacc) {

    // À faire... L'exemple ci-dessous n'est pas fonctionnel.
    if ((vacc < 64) || (vacc > 191)) {
        accumulateur.accumulateurPresent = 0;
        accumulateur.accumulateurDisponible = 0;
    } else {
        accumulateur.accumulateurPresent = 1;
        if (vacc > 127) {
            accumulateur.accumulateurDisponible = 1;
        } else {
            accumulateur.accumulateurDisponible = 0;            
        }
    }

    return &accumulateur;
}

#ifdef TEST

static void peut_detecter_que_l_accumulateur_est_present() {
    initialiseAccumulateur();
    verifieEgalite("ACCPR1", mesureAccumulateur(63)->accumulateurPresent, 0);
    verifieEgalite("ACCPR2", mesureAccumulateur(64)->accumulateurPresent, 1);
    verifieEgalite("ACCPR3", mesureAccumulateur(191)->accumulateurPresent, 1);
    verifieEgalite("ACCPR4", mesureAccumulateur(192)->accumulateurPresent, 0);
}

static void peut_detecter_que_l_accumulateur_est_disponible() {
    initialiseAccumulateur();
    
    verifieEgalite("ACCDI1", mesureAccumulateur(126)->accumulateurDisponible, 0);
    verifieEgalite("ACCDI2", mesureAccumulateur(127)->accumulateurDisponible, 0);
    verifieEgalite("ACCDI3", mesureAccumulateur(128)->accumulateurDisponible, 1);
    verifieEgalite("ACCDI4", mesureAccumulateur(129)->accumulateurDisponible, 1);
}

static void solicite_l_accumulateur_si_l_alimentation_defaille() {
    initialiseAccumulateur();

    verifieEgalite("ACCAD1", mesureAlimentation(125)->accumulateurSollicite, 1);
    verifieEgalite("ACCAD2", mesureAlimentation(126)->accumulateurSollicite, 1);
    verifieEgalite("ACCAD3", mesureAlimentation(127)->accumulateurSollicite, 0);
    verifieEgalite("ACCAD4", mesureAlimentation(128)->accumulateurSollicite, 0);
}

void testeAccumulateur() {
    peut_detecter_que_l_accumulateur_est_present();
    peut_detecter_que_l_accumulateur_est_disponible();
    
    solicite_l_accumulateur_si_l_alimentation_defaille();
}

#endif