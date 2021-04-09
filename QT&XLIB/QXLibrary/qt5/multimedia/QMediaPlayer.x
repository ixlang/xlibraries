//xlang Source, Name:qt5/multimedia/QMediaPlayer.x 
//Date: Thu Mar 14:37:32 2021 
package Qt{
    public class QMediaPlayer : QMediaObject{
        public QMediaPlayer(){
        }
        
        public QMediaPlayer(long handle){
            super(handle);
        }
        
        public bool create(Flag f) {
            nativehandle = QtXnl.createQPObject(QType.qtMediaPlayer, this, 0l, (long)f, 0l, 0l, 0l);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QObject parent, Flag f) {
            nativehandle = QtXnl.createQPObject(QType.qtMediaPlayer, this, parent.nativehandle, (long)f, 0l, 0l, 0l);
            if (nativehandle == 0){
                return false;
            }
            return true;
        } 
        
        public enum Flag
        {
            Default = 0,
            LowLatency = 0x01,
            StreamPlayback = 0x02,
            VideoSurface = 0x04
        };
        
        public enum Error
        {
            NoError,
            ResourceError,
            FormatError,
            NetworkError,
            AccessDeniedError,
            ServiceMissingError,
            MediaIsPlaylist
        };
        
        public enum State
        {
            StoppedState,
            PlayingState,
            PausedState
        };

        public enum MediaStatus
        {
            UnknownMediaStatus,
            NoMedia,
            LoadingMedia,
            LoadedMedia,
            StalledMedia,
            BufferingMedia,
            BufferedMedia,
            EndOfMedia,
            InvalidMedia
        };
        
        public static SupportEstimate hasSupport(String mimeType, String [] codecs, Flag flags){
            return (SupportEstimate)QtXnl.long_object_string((long)flags, Constant.QMEDIAPLAYER_HASSUPPORT, codecs, mimeType);
        }
        
        public static String[] supportedMimeTypes(Flag flags){
            return (String[]) QtXnl.object_get_handle(0, Constant.QMEDIAPLAYER_SUPPORTEDMIMETYPES, (long)flags);
        }
        
        public void setVideoOutput(QVideoWidget w){
            QtXnl.core_getintlong(nativehandle, Constant.QMEDIAPLAYER_SETVIDEOOUTPUT, w.nativehandle);
        }

        public State state(){
            return (State)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_STATE);
        }
        
        public MediaStatus mediaStatus() {
            return (MediaStatus)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_MEDIASTATUS);
        }

        public long duration() {
            return QtXnl.long_get(nativehandle, Constant.QMEDIAPLAYER_DURATION);
        }
        
        public long position(){
            return QtXnl.long_get(nativehandle, Constant.QMEDIAPLAYER_POSITION);
        }

        public int volume() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_VOLUME);
        }
        
        public bool isMuted() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAPLAYER_ISMUTED);
        }
        
        public bool isAudioAvailable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAPLAYER_ISAUDIOAVAILABLE);
        }
        
        public bool isVideoAvailable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAPLAYER_ISVIDEOAVAILABLE);
        }

        public int bufferStatus() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_BUFFERSTATUS);
        }

        public bool isSeekable() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QMEDIAPLAYER_ISSEEKABLE);
        }
        
        public double playbackRate() {
            return QtXnl.widget_get_double_value(nativehandle, Constant.QMEDIAPLAYER_PLAYBACKRATE);
        }

        public Error error() {
            return (Error)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_ERROR);
        }
        
        public String errorString() {
            return (String)QtXnl.core_getString(nativehandle, Constant.QMEDIAPLAYER_ERRORSTRING);
        }

        public AvailabilityStatus availability() {
            return (AvailabilityStatus)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_AVAILABILITY);
        }

        public QAudio.Role audioRole(){
            return (QAudio.Role)QtXnl.widget_get_int_value(nativehandle, Constant.QMEDIAPLAYER_AUDIOROLE);
        }
        
        public void setAudioRole(QAudio.Role audioRole){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QMEDIAPLAYER_SETAUDIOROLE, (int)audioRole);
        }
        
        public QAudio.Role [] supportedAudioRoles() {
            return (QAudio.Role [])QtXnl.widget_get_object(nativehandle, Constant.QMEDIAPLAYER_SUPPORTEDAUDIOROLES);
        }
        
        public void play(){
            QtXnl.widget_slot(nativehandle, Constant.QMEDIAPLAYER_PLAY);
        }
        public void pause(){
            QtXnl.widget_slot(nativehandle, Constant.QMEDIAPLAYER_PAUSE);
        }
        public void stop(){
            QtXnl.widget_slot(nativehandle, Constant.QMEDIAPLAYER_STOP);
        }

        public void setPosition(long position){
            QtXnl.widget_set_native_value(nativehandle, Constant.QMEDIAPLAYER_SETPOSITION, position);
        }
        public void setVolume(int volume){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QMEDIAPLAYER_SETVOLUME, volume);
        }
        public void setMuted(bool muted){
            QtXnl.widget_set_bool_value(nativehandle, Constant.QMEDIAPLAYER_SETMUTED, muted);
        }
        public void setPlaybackRate(double rate){
            QtXnl.widget_set_double_value(nativehandle, Constant.QMEDIAPLAYER_SETPLAYBACKRATE, rate);
        }
        public void setMedia(String uri){
            QtXnl.widget_slot_string(nativehandle, Constant.QMEDIAPLAYER_SETMEDIA, uri);
        }
        
        onMediaPlayerListener __listener = nilptr;
        
        public void setOnMediaPlayerListenerk(onMediaPlayerListener _l){
            __listener = _l;
        }
        public onMediaPlayerListener getOnMediaPlayerListenerk(){
            return __listener;
        }
        
        public void mediaChanged(String uri){
            if (__listener != nilptr){
                __listener.mediaChanged(this,uri);
            }
        }
        public void currentMediaChanged(String uri){
            if (__listener != nilptr){
                __listener.currentMediaChanged(this,uri);
            }
        }
        public void stateChanged(State newState){
            if (__listener != nilptr){
                __listener.stateChanged(this, newState);
            }
        }
        public void mediaStatusChanged(MediaStatus status){
            if (__listener != nilptr){
                __listener.mediaStatusChanged(this, status);
            }
        }
        public void durationChanged(long duration){
            if (__listener != nilptr){
                __listener.durationChanged(this, duration);
            }
        }
        public void positionChanged(long position){
            if (__listener != nilptr){
                __listener.positionChanged(this, position);
            }
        }
        public void volumeChanged(int volume){
            if (__listener != nilptr){
                __listener.volumeChanged(this, volume);
            }
        }
        public void mutedChanged(bool muted){
            if (__listener != nilptr){
                __listener.mutedChanged(this, muted);
            }
        }
        public void audioAvailableChanged(bool available){
            if (__listener != nilptr){
                __listener.audioAvailableChanged(this, available);
            }
        }
        public void videoAvailableChanged(bool videoAvailable){
            if (__listener != nilptr){
                __listener.videoAvailableChanged(this, videoAvailable);
            }
        }
        public void bufferStatusChanged(int percentFilled){
            if (__listener != nilptr){
                __listener.bufferStatusChanged(this, percentFilled);
            }
        }
        public void seekableChanged(bool seekable){
            if (__listener != nilptr){
                __listener.seekableChanged(this, seekable);
            }
        }
        public void playbackRateChanged(double rate){
            if (__listener != nilptr){
                __listener.playbackRateChanged(this, rate);
            }
        }
        public void audioRoleChanged(QAudio.Role role){
            if (__listener != nilptr){
                __listener.audioRoleChanged(this, role);
            }
        }
        public void error(QMediaPlayer.Error error){
            if (__listener != nilptr){
                __listener.error(this, error);
            }
        }
    };
};