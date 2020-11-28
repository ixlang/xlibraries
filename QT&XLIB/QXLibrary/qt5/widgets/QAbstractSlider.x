//xlang Source, Name:qt5/widgets/QAbstractSlider.x 
//Date: Thu Oct 16:40:58 2020 

package Qt{
    public class QAbstractSlider : QWidget{

        public static class SliderEventListener{
            public void onValueChanged(QAbstractSlider, int value) {

            }

            public void onPressed(QAbstractSlider) {

            }

            public void onMoved(QAbstractSlider, int position) {

            }

            public void onReleased(QAbstractSlider) {

            }

            public void onRangeChanged(QAbstractSlider, int min, int max) {

            }

            public void onActionTriggered(QAbstractSlider, int action) {

            }
        };
        
        SliderEventListener listener = nilptr;
        
        public QAbstractSlider(){
            
        }
        
        public QAbstractSlider(long handle){
            super(handle);
        }

        public void setSliderEventListener(SliderEventListener l){
            listener = l;
        }
        
        public SliderEventListener getSliderEventListener(){
            return listener;
        }
        
        public void setMinimum(int v){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETMIN, v);
        }
        
        public int minimum() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETMIN);
        }

        public void setMaximum(int v){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETMAX, v);
        }
        
        public int maximum() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETMAX);
        }

        public void setSingleStep(int v){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETSINGLESTEP, v);
        }
        
        public int singleStep() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETSINGLESTEP);
        }

        public void setPageStep(int v){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETPAGESTEP, v);
        }
        
        public int pageStep() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETPAGESTEP);
        }

        public void setTracking(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.SLD_SETTRACKING, enable);
        }
        
        public bool hasTracking() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.SLD_GETTRACKING);
        }

        public void setSliderDown(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.SLD_SETSLIDDOWN, enable);
        }
        
        public bool isSliderDown() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.SLD_GETSLIDDOWN);
        }

        public void setSliderPosition(int v){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETSLIDPOS, v);
        }
        
        public int sliderPosition() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETSLIDPOS);
        }

        public void setInvertedAppearance(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.SLD_SETINVERTEDAPPEARANCE, enable);
        }
        
        public bool invertedAppearance() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.SLD_GETINVERTEDAPPEARANCE);
        }

        public void setInvertedControls(bool enable){
            QtXnl.widget_set_bool_value(nativehandle, Constant.SLD_SETINVERTEDCONTROLS, enable);
        }
        
        public bool invertedControls() {
            return QtXnl.widget_get_bool_value(nativehandle, Constant.SLD_GETINVERTEDCONTROLS);
        }

        public enum SliderAction {
            SliderNoAction,
            SliderSingleStepAdd,
            SliderSingleStepSub,
            SliderPageStepAdd,
            SliderPageStepSub,
            SliderToMinimum,
            SliderToMaximum,
            SliderMove
        };

        public int value() {
            return QtXnl.widget_get_int_value(nativehandle, Constant.SLD_GETVALUE);
        }

        public void triggerAction(SliderAction action){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_TRIGGERACTION, action);
        }


        public void setValue(int v){
            QtXnl.widget_set_vint_value(nativehandle,Constant. SLD_SETVALUE, v);
        }
        
        public void setOrientation(int orientation){
            QtXnl.widget_set_vint_value(nativehandle, Constant.SLD_SETORIENTATION, orientation);
        }
        
        public void setRange(int min, int max){
            QtXnl.widget_set_v2int_value(nativehandle,Constant. SLD_SETRANGE, min, max);
        }
        
        //
        
        public void onValueChanged(int value) {
            if (listener != nilptr){
                listener.onValueChanged(this, value);
            }
        }

        public void onPressed() {
            if (listener != nilptr){
                listener.onPressed(this);
            }
        }
        
        public void onMoved(int position) {
            if (listener != nilptr){
                listener.onMoved(this, position);
            }
        }
        
        public void onReleased() {
            if (listener != nilptr){
                listener.onReleased(this);
            }
        }

        public void onRangeChanged(int min, int max) {
            if (listener != nilptr){
                listener.onRangeChanged(this, min, max);
            }
        }

        public void onActionTriggered(int action) {
            if (listener != nilptr){
                listener.onActionTriggered(this, action);
            }
        }
    };
};