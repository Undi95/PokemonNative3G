package fr.undi.pokemonnative3g;

import android.content.Intent;
import android.net.Uri;

import org.libsdl.app.SDLActivity;

import java.io.File;

// L'activité de SDL charge libSDL2.so puis libmain.so (le jeu) et appelle son main()
public class GameActivity extends SDLActivity {
    // PokemonNative3G : variante debugtools, appelé par le jeu (src/platform/devtools.c) après un rapport de bug :
    // propose de l'envoyer (mail, messagerie, Drive…) par ReportProvider
    public static void shareReport(final String path) {
        final SDLActivity activity = (SDLActivity) mSingleton;
        if (activity == null)
            return;
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Uri uri = Uri.parse("content://" + activity.getPackageName() + ".rapports/" + new File(path).getName());
                Intent send = new Intent(Intent.ACTION_SEND);
                send.setType("application/x-tar");
                send.putExtra(Intent.EXTRA_STREAM, uri);
                send.putExtra(Intent.EXTRA_SUBJECT, "Rapport de bug PokemonNative3G");
                send.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                activity.startActivity(Intent.createChooser(send, "Envoyer le rapport de bug"));
            }
        });
    }
}
