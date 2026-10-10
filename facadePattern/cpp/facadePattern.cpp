#include<iostream>
using namespace std;

// sub-systems
class PowerSupply {
public:
    void providePower() {
        cout << "Power supply on: providing power..." << endl;
    }
};

class CoolingSystem {
public:
    void startFans() {
        cout << "Cooling system on: fans started..." << endl;
    }
};

class CPU {
public:
    void initialize() {
        cout << "CPU on: initializing CPU..." << endl;
    }
};

class Memory {
public:
    void selfTest() {
        cout << "Memory: self-test passed..." << endl;
    }
};

class HardDisk {
public:
    void spinup() {
        cout << "Hard drive: spinning up..." << endl;
    }
};

class BIOS {
public:
    void boot(CPU &c, Memory &m) {
        cout << "BIOS: Booting CPU and Memory checks..." << endl;
        c.initialize();
        m.selfTest();
    }
};

class OperatingSystem {
public:
    void load() {
        cout << "Operating system: loading into memory..." << endl;
    }
};


// facade
class ComputerFacade {
private:
    PowerSupply ps;
    CoolingSystem cs;
    CPU cpu;
    Memory memory;
    HardDisk hdd;
    BIOS bios;
    OperatingSystem os;
public:
    void startComputer() {
        cout << "----------Start Computer------------" << endl;
        ps.providePower();
        cs.startFans();
        bios.boot(cpu, memory);
        hdd.spinup();
        os.load();
        cout << "Computer loaded successfully" << endl;
    }
};

//client
int main() {
    ComputerFacade computer;
    computer.startComputer();
    
    return 0;
}