//xlang Source, Name:qt5/widgets/QVBoxLayout.x 
//Date: Wed May 01:54:38 2020 
package Qt{
    public class QVBoxLayout : QBoxLayout{
        public QVBoxLayout(){

        }
        public QVBoxLayout(long h){
            super(h);
        }
        public bool create(@NotNilptr QWidget parent){
            nativehandle = QtXnl.createQObject(QType.qtVLayout, this, parent.nativehandle);
            if (nativehandle == 0){
                return false;
            }
            return true;
        }
    };
};