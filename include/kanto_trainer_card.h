#ifndef GUARD_KANTO_TRAINER_CARD_H
#define GUARD_KANTO_TRAINER_CARD_H

// PokemonNative3G : la carte du joueur à Kanto (src/kanto_trainer_card.c : trainer_card.c de Rouge Feu). Le start menu
// passe par ShowPlayerTrainerCard d'Émeraude, qui ouvre celle-ci quand le joueur est à Kanto ; SELECT passe de l'une à
// l'autre.
void Kanto_ShowPlayerTrainerCard(void (*callback)(void));
// trainer_card.c : la carte de Hoenn (Émeraude), ouverte par SELECT depuis celle de Kanto
void ShowHoennPlayerTrainerCard(void (*callback)(void));

#endif // GUARD_KANTO_TRAINER_CARD_H
