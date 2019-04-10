SUBDIRS = ./xnl

all: $(SUBDIRS)  
	for dir in $(SUBDIRS); do cd $$dir && make && cd ../../;done;
  
clean: $(SUBDIRS)  
	for dir in $(SUBDIRS); do cd $$dir && make clean && cd ../../;done;  
	rm -f `find -name "*~"` || /bin/true
