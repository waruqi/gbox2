# includes
include $(PRO_DIR)/prefix.mak

# debug
#ifeq ($(DEBUG),y)
ANT_DEBUG 	:= debug
#else
#ANT_DEBUG 	:= release
#endif

# make all
all : .null
	$(SDK)/tools/android -v update project -p .
	export NDK_PROJECT_PATH=${shell pwd}
	$(NDK)/ndk-build
	ant $(ANT_DEBUG)

# make install
install : .null
	$(MKDIR) $(BIN_DIR)/bin
	$(CP) ./bin/*.apk $(BIN_DIR)/bin

# make clean
clean : .null
	-@$(RM) ./jni/*.o
	-@$(RMDIR) -rf ./gen
	-@$(RMDIR) -rf ./obj
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

