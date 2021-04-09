//xlang Source, Name:qt5/multimedia/QAudio.x 
//Date: Thu Mar 14:44:27 2021 
package Qt{
    public class QAudio{
        public enum Error { NoError, OpenError, IOError, UnderrunError, FatalError };
        public enum State { ActiveState, SuspendedState, StoppedState, IdleState };
        public enum Mode { AudioInput, AudioOutput };

        public enum Role {
            UnknownRole,
            MusicRole,
            VideoRole,
            VoiceCommunicationRole,
            AlarmRole,
            NotificationRole,
            RingtoneRole,
            AccessibilityRole,
            SonificationRole,
            GameRole
        };

        public enum VolumeScale {
            LinearVolumeScale,
            CubicVolumeScale,
            LogarithmicVolumeScale,
            DecibelVolumeScale
        };
    };
};