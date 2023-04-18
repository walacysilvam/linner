#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <errno.h>

using namespace std;

class Linner {
    public:
        void start() {
            int check = mkdir("lnn", 0777);
            ofstream arq;

            time_t startTime;
            startTime = time(NULL);
            struct tm tm = *localtime(&startTime);

            if (!check) {
                int main = mkdir("lnn/main", 0777);
                arq.open("./lnn/lnn_p.txt");
                arq << "start_point: [init]" << tm.tm_mday << tm.tm_mon << tm.tm_year + 1900 << tm.tm_hour << tm.tm_min;
                cout << "Linner started:: add archive for begin." << endl;
            } else {
                cout << "Erro ao criar diretorio." << endl;
            }
        }

        void add(char *arq) {
            ifstream arc(arq, ios::binary);
            if (!arc.is_open()) {
                cerr << "Linner error:: read error: failed to read archive: " << strerror(errno) << endl;
                return;
            }

            ofstream dst("./lnn/main/arc_teste.txt", ios::binary);
            if (!dst.is_open()) {
                arc.close();
                cerr << "Linner error: read error: failed to open destiny archive: " << strerror(errno) << endl;
                return;
            }

            unsigned char buf[1024 * 8];
            size_t n = 0;
            size_t m = 0;

            do {
                m = 0;
                n = arc.read(reinterpret_cast<char*>(buf), sizeof(buf)).gcount();

                if (n > 0) {
                    dst.write(reinterpret_cast<char*>(buf), n);
                    m = dst.tellp();
                }

            } while ((n > 0) && (n == m));

            arc.close();
            dst.close();

            if (m) {
                cerr << "Linner error:: copy error: failed to copy archive: " << strerror(errno) << endl;
                remove("./lnn/main/arc_teste.txt");
            }
        }
};

int main(int argc, char *argv[]) {
    Linner l;

    if (argc > 1) {
        if (!strcmp(argv[1], "start")) {
            cout << "O argumento passado foi: " << argv[1] << endl;
            l.start();
        }

        if ((!strcmp(argv[1], "add")) && (argc > 2)) {
            l.add(argv[2]);
        }
    }

    return 0;
}
