# includes
include $(PRO_DIR)/prefix.mak

# make all
all : .null
	xcodebuild

# make install
install : .null
	-$(RMDIR) $(BIN_DIR)/bin
	$(MKDIR) $(BIN_DIR)/bin
	xcrun -sdk iphoneos PackageApplication -v ./build/Release-iphoneos/demo.app -o $(BIN_DIR)/bin/demo.ipa

# make clean
clean : .null
	-@$(RMDIR) ./build

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

