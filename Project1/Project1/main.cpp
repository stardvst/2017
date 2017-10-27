#include <iostream>
#include <cstdio>
#include <string>

enum class PersistenceType { File, Queue, Pathway };

struct PersistenceAttribute {
    PersistenceType type;
    char value[30];
};

struct DistrWorkPackage {
    DistrWorkPackage(char *type) {
        sprintf(desc, "Distr. work package for: %s", type);
    }

    void setFile(char *f, char *v) {
        sprintf(tmp, "\n File(%s): %s", f, v);
        strcat(desc, tmp);
    }

    void setQueue(char *q, char *v) {
        sprintf(tmp, "\n Queue(%s): %s", q, v);
        strcat(desc, tmp);
    }

    void setPathway(char *p, char *v) {
        sprintf(tmp, "\n Pathway(%s): %s", p, v);
        strcat(desc, tmp);
    }

    const char *getState() const { return desc; }
private:
    char desc[200];
    char tmp[80];
};

/**
    Builder abstract class
*/
struct Builder {
    virtual void configureFile(char *f) = 0;
    virtual void configureQueue(char *q) = 0;
    virtual void configurePathway(char *p) = 0;
    DistrWorkPackage *getResult() const { return result; }
protected:
    DistrWorkPackage *result;
};

/**
    Derived builder classes
*/
struct UnixBuilder : Builder {
    UnixBuilder() { result = new DistrWorkPackage("Unix"); }

    void configureFile(char *f) { result->setFile("flatFile", f); }
    void configureQueue(char *q) { result->setQueue("FIFO", q); }
    void configurePathway(char *p) { result->setPathway("thread", p); }
};

struct VmsBuilder : Builder {
    VmsBuilder() { result = new DistrWorkPackage("Vms"); }

    void configureFile(char *f) { result->setFile("ISAM", f); }
    void configureQueue(char *q) { result->setQueue("pririty", q); }
    void configurePathway(char *p) { result->setPathway("LWP", p); }
};

/**
    Reader (director)
*/
struct Reader {
    void setBuilder(Builder *b) { builder = b; }
    void construct(PersistenceAttribute list[], int num) {
        for(int i = 0; i < num; ++i)
            if(list[i].type == PersistenceType::File)
                builder->configureFile(list[i].value);
            else if(list[i].type == PersistenceType::Queue)
                builder->configureQueue(list[i].value);
            else if(list[i].type == PersistenceType::Pathway)
                builder->configurePathway(list[i].value);
    }
private:
    Builder *builder;
};

int main() {

    PersistenceAttribute input[] = {
        { PersistenceType::File, "state.dat" },
        { PersistenceType::File, "config.sys" },
        { PersistenceType::Queue, "compute" },
        { PersistenceType::Queue, "log" },
        { PersistenceType::Pathway, "authentication" },
        { PersistenceType::Pathway, "error processing" }
    };

    Reader reader;
    
    UnixBuilder unix_builder;
    reader.setBuilder(&unix_builder);
    reader.construct(input, 6);
    std::cout << unix_builder.getResult()->getState() << std::endl;

    VmsBuilder vms_builder;
    reader.setBuilder(&vms_builder);
    reader.construct(input, 6);
    std::cout << vms_builder.getResult()->getState() << std::endl;

    std::cin.get();
    return 0;
}
