#include <string>
class FsDirectory {
public:
    virtual std::string getName();
    virtual FsDirectory* getParent();
    virtual FsDirectory* getDirectory(); 
    virtual ~FsDirectory();
};
