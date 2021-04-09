//xlang Source, Name:qt5/multimedia/QAudioDeviceInfo.x 
//Date: Sat Mar 02:19:58 2021 
package Qt{
    public class QAudioDeviceInfo : QCore{
        
        private QAudioDeviceInfo(long h){
            super(h);
        }
        
        public bool isNull() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QAUDIODEVICEINFO_ISNULL);
        }

        public String deviceName() {
            return (String)QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_NAME);
        }

        public bool isFormatSupported(QAudioFormat format) {
            return QtXnl.core_getintlong(nativehandle, Constant.QAUDIODEVICEINFO_ISFORMATSUPPORTED, format.nativehandle) != 0;
        }
        
        public QAudioFormat preferredFormat() {
            return new QAudioFormat(QtXnl.long_get(nativehandle, Constant.QAUDIODEVICEINFO_PREFERREDFORMAT));
        }
        
        public QAudioFormat nearestFormat(QAudioFormat format) {
            return new QAudioFormat(QtXnl.object_get_long_int(nativehandle, Constant.QAUDIODEVICEINFO_NEARESTFORMAT, format.nativehandle, 0));
        }

        public String[] supportedCodecs(){
            return (String[])QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDCODECS);
        }
        
        public int[] supportedSampleRates() {
            return (int[])QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDSAMPLERATES);
        }
        
        public int[] supportedChannelCounts() {
            return (int[])QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDCHANNELCOUNTS);
        }
        
        public int[] supportedSampleSizes() {
            return (int[])QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDSAMPLESIZES);
        }
        
        public int supportedByteOrders() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDBYTEORDERS);
        }
        
        public QAudioFormat.SampleType [] supportedSampleTypes() {
            return (QAudioFormat.SampleType[])QtXnl.core_getString(nativehandle, Constant.QAUDIODEVICEINFO_SUPPORTEDSAMPLETYPES);
        }

        public static QAudioDeviceInfo defaultInputDevice(){
            return new QAudioDeviceInfo(QtXnl.long_get(0, Constant.QAUDIODEVICEINFO_DEFAULTINPUTDEVICE));
        }
        
        public static QAudioDeviceInfo defaultOutputDevice(){
            return new QAudioDeviceInfo(QtXnl.long_get(0, Constant.QAUDIODEVICEINFO_DEFAULTOUTPUTDEVICE));
        }

        public static QAudioDeviceInfo[] availableDevices(QAudio.Mode mode){
            long [] ha = (long []) QtXnl.object_get_handle(0l, Constant.QAUDIODEVICEINFO_AVAILABLEDEVICES, mode);
            if (ha != nilptr){
                QAudioDeviceInfo[] qai = new QAudioDeviceInfo[ha.length];
                for (int i = 0; i < ha.length; i++){
                    qai[i] = new QAudioDeviceInfo(ha[i]);
                }
                return qai;
            }
            return nilptr;
        }
        
        public void finalize(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIODEVICEINFO_FINALIZE);
        }
    };
};
