#include <iostream>
#include "UI.h"

int main() {


    vector<TElem> V;
    Repository repo{V};
    TElem elem1{"E_Coli_K12", "yqgE", "ATGACATCATCATTG"};
    TElem elem2{"M_tuberculosis", "ppiA", "TCTTCATCATCATCGG"};
    TElem elem3{"Mouse", "Col2a1", "TTAAAGCATGGCTCTGTG"};
    TElem elem4{"E_Coli_ETEC", "yqgE", "GTGACAGCGCCCTTCTTTCCACG"};
    TElem elem5{"E_Coli_K12", "hokC", "TTAATGAAGCATAAGCTTGATTTC"};

    repo.addGene(elem1);
    repo.addGene(elem2);
    repo.addGene(elem3);
    repo.addGene(elem4);
    repo.addGene(elem5);

    Service service{repo};
    ui ui{service};

    ui.start_application();
    return 0;
}
