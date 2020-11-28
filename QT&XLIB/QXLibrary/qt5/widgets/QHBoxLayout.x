//xlang Source, Name:qt5/widgets/QHBoxLayout.x 
//Date: Wed May 01:54:15 2020 
package Qt{
public class QHBoxLayout : QBoxLayout{

    public QHBoxLayout(){

    }
    
    public QHBoxLayout(long h){
        super(h);
    }
    
    public bool create(@NotNilptr QWidget parent){
        nativehandle = QtXnl.createQObject(QType.qtHLayout, this, parent.nativehandle);
        if (nativehandle == 0){
            return false;
        }
        return true;
    }

};
};