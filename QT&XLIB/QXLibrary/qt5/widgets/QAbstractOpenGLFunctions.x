//xlang Source, Name:qt5/widgets/QAbstractOpenGLFunctions.x 
//Date: Tue Mar 21:28:49 2021 
package Qt{
    class QAbstractOpenGLFunctions : QCore{
        protected QAbstractOpenGLFunctions(){
            
        }
        public QAbstractOpenGLFunctions(long h){
            super(h);
            if (h == 0){
                throw new IllegalArgumentException("could not new Object");
            }
        }
        public bool initializeOpenGLFunctions(){
            return false;
        }
    };
};