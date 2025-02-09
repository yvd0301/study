import org.freedesktop.gstreamer.*;
import org.freedesktop.gstreamer.elements.*;

public class RTSPServer {
    public static void main(String[] args) {
        Gst.init("RTSPServer");

        Pipeline pipeline = new Pipeline();
        Element videoSrc = ElementFactory.make("v4l2src", "video-source"); // 카메라 입력을 가져
        Element videoEnc = ElementFactory.make("x264enc", "encoder"); // H.264 비디오 인코딩 수행
        Element rtpPay = ElementFactory.make("rtph264pay", "rtp-payload"); // RTP 페이로드 변환
        Element udpSink = ElementFactory.make("udpsink", "udp-sink"); // UDP를 통해 실시간 전송

        udpSink.set("host", "192.168.1.100"); // 클라이언트 IP 주소
        udpSink.set("port", 5004);  // RTP 스트리밍 포트

        pipeline.addMany(videoSrc, videoEnc, rtpPay, udpSink);
        Element.linkMany(videoSrc, videoEnc, rtpPay, udpSink);

        pipeline.play();

        System.out.println("RTP Server is streaming...");
    }
}
