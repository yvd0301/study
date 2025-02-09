import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.widget.VideoView;

public class RTPClient extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        VideoView videoView = findViewById(R.id.videoView);
        String videoUrl = "rtp://192.168.1.100:5004"; // server address

        videoView.setVideoURI(Uri.parse(videoUrl));
        videoView.start();
    }
}
