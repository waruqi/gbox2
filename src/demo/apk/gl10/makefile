# includes
include $(PRO_DIR)/prefix.mak

# debug
ifeq ($(DEBUG),y)
ANT_DEBUG := debug
else
ANT_DEBUG := release
endif

# make all
all : .null
	ant $(ANT_DEBUG) -buildfile ./build.xml

# make install
install : .null
	$(MKDIR) $(BIN_DIR)/bin
	$(CP) ./bin/demo-$(ANT_DEBUG).apk $(BIN_DIR)/bin

# make clean
clean : .null
	-@$(RMDIR) -rf ./gen
	-@$(RMDIR) -rf ./bin

# make update
update : .null

# make output
output : .null

# make error
error : .null

# make warning
warning : .null

# make doc
doc : .null

.null :

