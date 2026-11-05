// PokemonNative3G : version navigateur. Lié juste après les objets du jeu, avant ceux de src/platform/ (Makefile,
// cible web) : marque la fin de leurs variables à zéro (src/platform/system.c, GetGameRam)
unsigned char gWebGameRamEnd[4];
