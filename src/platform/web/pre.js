// PokemonNative3G : version navigateur (docs/NAVIGATEUR.md), lu par emcc (--pre-js) avant le code du jeu.
//
// La sauvegarde (pokeemerald.sav) et les options (pokeemerald.ini) sont dans le dossier /sauvegarde, gardé dans
// IndexedDB (IDBFS). Il est relu avant main (le jeu lit la sauvegarde dès le démarrage), puis recopié dans IndexedDB
// après chaque écriture du jeu (SyncStorage dans src/platform/sdl2.c appelle Module.sauvegardeModifiee).

Module.preRun = Module.preRun || [];
Module.preRun.push(function () {
  FS.mkdir('/sauvegarde');
  FS.mount(IDBFS, {}, '/sauvegarde');
  addRunDependency('sauvegarde');
  FS.syncfs(true, function (err) {
    if (err) console.error('[sauvegarde] lecture depuis IndexedDB impossible', err);
    removeRunDependency('sauvegarde');
  });
});

// Les écritures arrivent par rafales (la sauvegarde du jeu écrit secteur par secteur) : une seule copie, juste après
(function () {
  var minuteur = null;
  var enCours = false;
  var encore = false;

  function copier() {
    minuteur = null;
    if (enCours) {
      encore = true;
      return;
    }
    enCours = true;
    FS.syncfs(false, function (err) {
      enCours = false;
      if (err) console.error('[sauvegarde] écriture dans IndexedDB impossible', err);
      if (Module.onSauvegarde) Module.onSauvegarde(err);
      if (encore) {
        encore = false;
        copier();
      }
    });
  }

  Module.sauvegardeModifiee = function () {
    if (minuteur === null) minuteur = setTimeout(copier, 200);
  };
})();
