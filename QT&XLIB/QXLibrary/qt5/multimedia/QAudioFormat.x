//xlang Source, Name:qt5/multimedia/QAudioFormat.x 
//Date: Fri Mar 21:27:28 2021 

package Qt{
    public class QAudioFormat  : QCore{
        public enum SampleType { Unknown, SignedInt, UnSignedInt, Float };
        public enum Endian { BigEndian , LittleEndian};
        
        public QAudioFormat(long h){
            super(h);
        }
        public QAudioFormat(){
            nativehandle = QtXnl.createNObject(QType.qtAudioFormat, 0);
            if (nativehandle == 0){
                throw new IllegalArgumentException("can not new QAudioFormat");
            }
        }
        
        public bool isvalid(){
            return QtXnl.widget_get_bool_value(nativehandle, Constant.QAUDIOFORMAT_ISVALID);
        }

        public void setSampleRate(int sampleRate){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOFORMAT_SETSAMPLERATE, sampleRate);
        }
        
        public int sampleRate() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_SAMPLERATE);
        }

        public void setChannelCount(int channelCount){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOFORMAT_SETCHANNELCOUNT, channelCount);
        }
        
        public int channelCount(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_CHANNELCOUNT);
        }

        public void setSampleSize(int sampleSize){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOFORMAT_SETSAMPLESIZE, sampleSize);
        }
        
        public int sampleSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_SAMPLESIZE);
        }

        public void setCodec(String codec){
            QtXnl.widget_slot_string(nativehandle, Constant.QAUDIOFORMAT_SETCODEC, codec);
        }
        
        public String codec() {
            return (String)QtXnl.core_getString(nativehandle, Constant.QAUDIOFORMAT_CODEC);
        }

        public void setByteOrder(Endian byteOrder){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOFORMAT_SETBYTEORDER, byteOrder);
        }
        
        public Endian byteOrder() {
            return (Endian)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_BYTEORDER);
        }

        public void setSampleType(SampleType sampleType){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOFORMAT_SETSAMPLETYPE, sampleType);
        }
        
        public SampleType sampleType() {
            return (SampleType)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_SAMPLETYPE);
        }

        // Helper functions
        public int bytesForDuration(long duration) {
            return QtXnl.core_getintlong(nativehandle, Constant.QAUDIOFORMAT_BYTESFORDURATION, duration);
        }
        
        public long durationForBytes(int byteCount) {
            return QtXnl.object_get_long_int(nativehandle, Constant.QAUDIOFORMAT_DURATIONFORBYTES, 0, byteCount);
        }

        public int bytesForFrames(int frameCount){
            return QtXnl.widget_set_bint_value(nativehandle, Constant.QAUDIOFORMAT_BYTESFORFRAMES, frameCount);
        }
        
        public int framesForBytes(int byteCount) {
            return QtXnl.widget_set_bint_value(nativehandle, Constant.QAUDIOFORMAT_FRAMESFORBYTES, byteCount);
        }

        public int framesForDuration(long duration){
            return QtXnl.core_getintlong(nativehandle, Constant.QAUDIOFORMAT_FRAMESFORDURATION, duration);
        }
        
        public long durationForFrames(int frameCount) {
            return QtXnl.object_get_long_int(nativehandle, Constant.QAUDIOFORMAT_DURATIONFORFRAMES, 0, frameCount);
        }

        public int bytesPerFrame() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOFORMAT_BYTESPERFRAME);
        }
        public void finalize(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOFORMAT_FINALIZE);
        }
    };
};