//xlang Source, Name:qt5/multimedia/QAudioOutput.x 
//Date: Fri Mar 21:12:34 2021 

package Qt{
    public class QAudioOutput : QObject{
        public QAudioOutput(){
        }
        
        public QAudioOutput(long handle){
            super(handle);
        }
                
        public bool create(@NotNilptr QObject parent, QAudioFormat f) {
            nativehandle = QtXnl.createQPObject(QType.qtAudioOutput, this, parent == nilptr ? 0l : parent.nativehandle, f == nilptr ? 0l : f.nativehandle, 0l, 0l, 0l);
            if (nativehandle == 0){
                return false;
            }
            return true;
        } 
        
        public QAudioFormat format() {
            return new QAudioFormat(QtXnl.long_get(nativehandle, Constant.QAUDIOOUTPUT_FORMAT));
        }

        public long write(Object [] data, int ofst, int len){
            return QtXnl.widget_set_int2_object_value(nativehandle, Constant.QAUDIOOUTPUT_WRITE, ofst, len, data);
        }
        
        public void start(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOOUTPUT_START);
        }

        public void stop(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOOUTPUT_STOP);
        }
        
        public void reset(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOOUTPUT_RESET);
        }
        
        public void suspend(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOOUTPUT_SUSPEND);
        }
        
        public void resume(){
            QtXnl.widget_slot(nativehandle, Constant.QAUDIOOUTPUT_RESUME);
        }

        public void setBufferSize(int bytes){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOOUTPUT_SETBUFFERSIZE, bytes);
        }
        
        public int bufferSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_BUFFERSIZE);
        }

        public int bytesFree() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_BYTESFREE);
        }
        
        public int periodSize() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_PERIODSIZE);
        }

        public void setNotifyInterval(int milliSeconds){
            QtXnl.widget_set_vint_value(nativehandle, Constant.QAUDIOOUTPUT_SETNOTIFYINTERVAL, milliSeconds);
        }
        
        public int notifyInterval(){
            return QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_NOTIFYINTERVAL);
        }

        public long processedUSecs() {
            return QtXnl.long_get(nativehandle, Constant.QAUDIOOUTPUT_PROCESSEDUSECS);
        }
        
        public long elapsedUSecs() {
            return QtXnl.long_get(nativehandle, Constant.QAUDIOOUTPUT_ELAPSEDUSECS);
        }

        public QAudio.Error error() {
            return (QAudio.Error)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_ERROR);
        }
        
        public QAudio.State state() {
            return (QAudio.State)QtXnl.widget_get_int_value(nativehandle, Constant.QAUDIOOUTPUT_STATE);
        }

        public void setVolume(double v){
            QtXnl.widget_set_double_value(nativehandle, Constant.QAUDIOOUTPUT_SETVOLUME, v);
        }
        
        public double volume() {
            return QtXnl.widget_get_double_value(nativehandle, Constant.QAUDIOOUTPUT_VOLUME);
        }
        
        //signal 
        onAudioOutputListener _lis;
        public void setOnAudioOutputListener(onAudioOutputListener l ){
            _lis = l;
        }
        public onAudioOutputListener getOnAudioOutputListener(){
            return _lis;
        }
        
        public void stateChanged(QAudio.State s){
            if (_lis != nilptr){
                _lis.stateChanged(this, s);
            }
        }
        
        public void notify(){
            if (_lis != nilptr){
                _lis.notify(this);
            }
        }
    };
};
