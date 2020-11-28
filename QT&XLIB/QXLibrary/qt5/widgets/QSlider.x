//xlang Source, Name:qt5/QXSlider.x 
//Date: Thu Oct 16:38:58 2020 
package Qt{

    public class QSlider : QAbstractSlider{

        public QSlider(){
        
        }
        
        public QSlider(long handle){
            super(handle);
        }
        
        public bool create()override {
            nativehandle = QtXnl.createQObject(QType.qtSlider, this, 0);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
        
        public bool create(@NotNilptr QWidget parent)override {
            nativehandle = QtXnl.createQObject(QType.qtSlider, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }    
    };
};