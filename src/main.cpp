#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Astronauta{
private:
 
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;
    int voosLancados;

public:

    Astronauta(string c, string n, int i){

        cpf = c;
        nome = n;
        idade = i;
        vivo = true;
        disponivel = true;
        voosLancados = 0;
    }    

    string getCpf(){
        return cpf;
    }
    string getNome(){
        return nome;
    }

    int getIdade(){
        return idade;
    }
    bool estaVivo(){
        return vivo;
    }
    bool estaDisponivel(){
        return disponivel;
    }
    int getVoosLancados(){
        return voosLancados;
    }
    void adicionarVooLancado(){
        voosLancados++;
    }
    void embarcar(){
        disponivel = false;
    }   
    void desembarcar(){
        disponivel = true;
    }  
    void morrer(){
        vivo = false;
        disponivel = false;
    }
};


class Voo{
private:

    int codigo;
    string estado;
    vector<string> cpfs;

public:

    Voo(int c){
        codigo = c;
        estado = "planejado";
    }

    int getCodigo(){
        return codigo;
    }
    string getEstado(){
        return estado;
    }
    int getQuantidadeAstronautas(){
        return cpfs.size();
    }
    string getCpf(int posicao){
        return cpfs[posicao];
    }

    bool temAstronauta(string cpf){
        
        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                return true;
            }
        }

        return false;
    }

    void adicionarAstronauta(string cpf){
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf){

        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }

        return false;
        
    } 

    void lancar(){
        estado = "em curso";
    }
    void explodir(){
        estado = "finalizado com explosao";
    }
    void finalizar(){
        estado = "finalizado com sucesso";
    }

};


class Agencia{
private:

    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf){
        
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].getCpf() == cpf) {
                return i;
            }
        }
        return -1;
    }

    int buscarVoo(int codigo){
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getCodigo() == codigo) {
                return i;
            }
        }
        return -1;
    }

public:
        
    void cadastrarAstronauta(string cpf, string nome, int idade){
        if (buscarAstronauta(cpf) != -1){
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
        }
        else{
            Astronauta astronauta(cpf, nome, idade);
            astronautas.push_back(astronauta);
            cout << "OK: astronauta " << cpf << " cadastrado" << endl;
        }
    }

    void cadastrarVoo(int codigo){
        if (buscarVoo(codigo) != -1){
            cout << "ERRO: Voo " << codigo << " ja cadastrado" << endl;
        }
        else{
            Voo voo(codigo);
            voos.push_back(voo);
            cout << "OK: voo " <<  codigo << " cadastrado" << endl;
        }
    }

    void adicionarAstronauta(string cpf, int codigo){
        int posicaoV = buscarVoo(codigo);
        int posicaoA = buscarAstronauta(cpf);

        if (buscarAstronauta(cpf) == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
        }
        else if (posicaoV == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicaoV].getEstado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        }
        else if (astronautas[posicaoA].estaVivo() == false){
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
        }
        else if (voos[posicaoV].temAstronauta(cpf) == true){
            cout << "ERRO: astronauta "<< cpf << " ja esta no voo " << codigo << endl;
        }
        else{
            voos[posicaoV].adicionarAstronauta(cpf);
            cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
        }
    }

    void removerAstronauta(string cpf, int codigo){
        int posicaoV = buscarVoo(codigo);
        int posicaoA = buscarAstronauta(cpf);

        if (posicaoA == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
        }
        else if (posicaoV == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicaoV].getEstado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        }
        else if (voos[posicaoV].temAstronauta(cpf) == false){
            cout << "ERRO: astronauta "<< cpf << " nao esta no voo " << codigo << endl;
        }
        else{
            voos[posicaoV].removerAstronauta(cpf);
            cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
        }
    }

    void lancarVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        else if(voos[posicao].getEstado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao planejado" << endl;
            return;
        }
        else if(voos[posicao].getQuantidadeAstronautas() <= 0){
            cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
            return;
        }
        for (int i = 0; i < voos[posicao].getQuantidadeAstronautas(); i++){
            string cpf = voos[posicao].getCpf(i);
            int posicaoA = buscarAstronauta(cpf);

            if (astronautas[posicaoA].estaVivo() == false){
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
            else if (astronautas[posicaoA].estaDisponivel() == false){
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
        }
        for (int i = 0; i < voos[posicao].getQuantidadeAstronautas(); i++){
            string cpf = voos[posicao].getCpf(i);
            int posicaoA = buscarAstronauta(cpf);
            astronautas[posicaoA].embarcar();
            astronautas[posicaoA].adicionarVooLancado();
        }
        voos[posicao].lancar();
        cout << "OK: voo " << codigo << " lancado" << endl;
    }

    void explodirVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicao].getEstado() != "em curso"){
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
        }
        else{
            for (int i = 0; i < voos[posicao].getQuantidadeAstronautas(); i++){
                string cpf = voos[posicao].getCpf(i);
                int posicaoA = buscarAstronauta(cpf);
                astronautas[posicaoA].morrer();
            }
            voos[posicao].explodir();
            cout << "OK: voo " << codigo << " explodiu" << endl;
        }
    }

    void finalizarVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        else if(voos[posicao].getEstado() != "em curso"){
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }
        else{
            for (int i = 0; i < voos[posicao].getQuantidadeAstronautas(); i++){
                string cpf = voos[posicao].getCpf(i);
                int posicaoA = buscarAstronauta(cpf);
                astronautas[posicaoA].desembarcar();
            }
            voos[posicao].finalizar();
            cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
        }
    }

    void imprimirVoo(Voo& voo){
        cout << "Voo " << voo.getCodigo() << ":";

        if (voo.getQuantidadeAstronautas() == 0) {
            cout << " sem astronautas";
        }
        else {
            for (int j = 0; j < voo.getQuantidadeAstronautas(); j++) {
                string cpf = voo.getCpf(j);
                int posicao = buscarAstronauta(cpf);

                if (posicao == -1) continue;

                cout << " " << astronautas[posicao].getCpf()
                    << " " << astronautas[posicao].getNome();

                if (j < voo.getQuantidadeAstronautas() - 1) {
                    cout << ",";
                }
            }
        }

        cout << "\n";
    }

    void listarVoos(){
        cout << "LISTA DE VOOS" << "\n";

        cout << "== planejado ==" << "\n";
        bool tem = false;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == "planejado") {
                imprimirVoo(voos[i]);
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";

        cout << "== em curso ==" << "\n";
        tem = false;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == "em curso") {
                imprimirVoo(voos[i]);
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";

        cout << "== finalizado com sucesso ==" << "\n";
        tem = false;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == "finalizado com sucesso") {
                imprimirVoo(voos[i]);
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";

        cout << "== finalizado com explosao ==" << "\n";
        tem = false;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getEstado() == "finalizado com explosao") {
                imprimirVoo(voos[i]);
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";
    }

    void listarMortos(){
        cout << "ASTRONAUTAS MORTOS" << "\n";
        bool tem = false;
        for (int i = 0; i < astronautas.size(); i++){
            if (!astronautas[i].estaVivo()){
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome() << " - voos: ";
                string cpf = astronautas[i].getCpf();

                bool primeiro = true;
                for (int j = 0; j < voos.size(); j++){
                    for (int k = 0; k < voos[j].getQuantidadeAstronautas(); k++){
                        if (voos[j].getCpf(k) == cpf){
                            if (!primeiro) cout << ", ";
                            cout << voos[j].getCodigo();
                            primeiro = false;
                        }
                    }
                }

                cout << "\n";
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";
    }

    void listarAstronautas(){
        cout << "LISTA DE ASTRONAUTAS" << "\n";

        cout << "== disponiveis ==" << "\n";
        bool tem = false;
        for (int i = 0; i < astronautas.size(); i++){
            if (astronautas[i].estaVivo() && !estaEmVooEmCurso(astronautas[i].getCpf())){
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << "\n";
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";

        cout << "== em voo ==" << "\n";
        tem = false;
        for (int i = 0; i < astronautas.size(); i++){
            if (astronautas[i].estaVivo()){
                int cod = codigoVooEmCurso(astronautas[i].getCpf());
                if (cod != -1){
                    cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                         << " (" << astronautas[i].getIdade() << " anos) - voo " << cod << "\n";
                    tem = true;
                }
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";

        cout << "== mortos ==" << "\n";
        tem = false;
        for (int i = 0; i < astronautas.size(); i++){
            if (!astronautas[i].estaVivo()){
                cout << astronautas[i].getCpf() << " " << astronautas[i].getNome()
                     << " (" << astronautas[i].getIdade() << " anos)" << "\n";
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum)" << "\n";
    }

    int codigoVooEmCurso(string cpf){
        for (int i = 0; i < voos.size(); i++){
            if (voos[i].getEstado() == "em curso" && voos[i].temAstronauta(cpf)){
                return voos[i].getCodigo();
            }
        }
        return -1;
    }

    bool estaEmVooEmCurso(string cpf){
        return codigoVooEmCurso(cpf) != -1;
    }

    void historico(string cpf){
        int posicao = buscarAstronauta(cpf);
        if (posicao == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << "\n";
            return;
        }

        cout << "HISTORICO DE " << astronautas[posicao].getCpf()
             << " " << astronautas[posicao].getNome() << "\n";

        bool tem = false;
        for (int i = 0; i < voos.size(); i++){
            if (voos[i].getEstado() != "planejado" && voos[i].temAstronauta(cpf)){
                cout << "voo " << voos[i].getCodigo() << ": " << voos[i].getEstado() << "\n";
                tem = true;
            }
        }
        if (!tem) cout << "(nenhum voo)" << "\n";
    }

    void salvar(string nome_arquivo){
        ofstream arquivo(nome_arquivo);
        if (!arquivo.is_open()){
            cout << "ERRO: nao foi possivel salvar em " << nome_arquivo << endl;
            return;
        }

        for (int i = 0; i < astronautas.size(); i++){
            arquivo << "ASTRONAUTA|" << astronautas[i].getCpf() << "|"
                    << astronautas[i].getIdade() << "|"
                    << (astronautas[i].estaVivo() ? 1 : 0) << "|"
                    << (astronautas[i].estaDisponivel() ? 1 : 0) << "|"
                    << astronautas[i].getVoosLancados() << "|"
                    << astronautas[i].getNome() << "\n";
        }

        for (int i = 0; i < voos.size(); i++){
            arquivo << "VOO|" << voos[i].getCodigo() << "|"
                    << voos[i].getEstado() << "|";
            for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++){
                if (j > 0) arquivo << ",";
                arquivo << voos[i].getCpf(j);
            }
            arquivo << "\n";
        }

        arquivo.close();
        cout << "OK: dados salvos em " << nome_arquivo << endl;
    }

    void carregar(string nome_arquivo){
        ifstream arquivo(nome_arquivo);
        if (!arquivo.is_open()){
            cout << "ERRO: nao foi possivel carregar de " << nome_arquivo << endl;
            return;
        }

        astronautas.clear();
        voos.clear();

        string linha;
        while (getline(arquivo, linha)){
            if (linha.empty()) continue;

            if (linha.substr(0, 11) == "ASTRONAUTA|"){
                vector<string> campos;
                string campo;
                for (int i = 0; i < linha.size(); i++){
                    if (linha[i] == '|'){
                        campos.push_back(campo);
                        campo = "";
                    } else {
                        campo += linha[i];
                    }
                }
                campos.push_back(campo);

                if (campos.size() < 7) continue;

                string cpf = campos[1];
                int idade = stoi(campos[2]);
                bool vivo = campos[3] == "1";
                bool disponivel = campos[4] == "1";
                int voosLancados = stoi(campos[5]);
                string nome = campos[6];

                Astronauta a(cpf, nome, idade);
                if (!vivo) a.morrer();
                else if (!disponivel) a.embarcar();
                for (int i = 0; i < voosLancados; i++){
                    a.adicionarVooLancado();
                }
                astronautas.push_back(a);
            }
            else if (linha.substr(0, 4) == "VOO|"){
                vector<string> campos;
                string campo;
                for (int i = 0; i < linha.size(); i++){
                    if (linha[i] == '|'){
                        campos.push_back(campo);
                        campo = "";
                    } else {
                        campo += linha[i];
                    }
                }
                campos.push_back(campo);

                int codigo = stoi(campos[1]);
                string estado = campos[2];

                Voo v(codigo);
                if (estado == "em curso") v.lancar();
                else if (estado == "finalizado com sucesso") v.lancar(), v.finalizar();
                else if (estado == "finalizado com explosao") v.lancar(), v.explodir();

                if (campos.size() > 3 && !campos[3].empty()){
                    string cpf;
                    for (int i = 0; i < campos[3].size(); i++){
                        if (campos[3][i] == ','){
                            v.adicionarAstronauta(cpf);
                            cpf = "";
                        } else {
                            cpf += campos[3][i];
                        }
                    }
                    if (!cpf.empty()) v.adicionarAstronauta(cpf);
                }

                voos.push_back(v);
            }
        }

        arquivo.close();
        cout << "OK: dados carregados de " << nome_arquivo << endl;
    }

    void relatorio(){
        int planejados = 0, emCurso = 0, sucesso = 0, explosao = 0;
        for (int i = 0; i < voos.size(); i++){
            if (voos[i].getEstado() == "planejado") planejados++;
            else if (voos[i].getEstado() == "em curso") emCurso++;
            else if (voos[i].getEstado() == "finalizado com sucesso") sucesso++;
            else if (voos[i].getEstado() == "finalizado com explosao") explosao++;
        }

        int cadastrados = astronautas.size();
        int vivos = 0, mortos = 0;
        for (int i = 0; i < astronautas.size(); i++){
            if (astronautas[i].estaVivo()) vivos++;
            else mortos++;
        }

        int maisExperiente = -1;
        int maxVoos = -1;
        for (int i = 0; i < astronautas.size(); i++){
            int vl = astronautas[i].getVoosLancados();
            if (vl > maxVoos){
                maxVoos = vl;
                maisExperiente = i;
            }
        }

        int finalizados = sucesso + explosao;
        int taxa = -1;
        if (finalizados > 0){
            taxa = sucesso * 100 / finalizados;
        }

        cout << "RELATORIO" << endl;
        cout << "voos planejados: " << planejados << endl;
        cout << "voos em curso: " << emCurso << endl;
        cout << "voos finalizados com sucesso: " << sucesso << endl;
        cout << "voos finalizados com explosao: " << explosao << endl;
        cout << "astronautas cadastrados: " << cadastrados << endl;
        cout << "astronautas vivos: " << vivos << endl;
        cout << "astronautas mortos: " << mortos << endl;
        if (maisExperiente == -1 || maxVoos == 0){
            cout << "astronauta mais experiente: (nenhum)" << endl;
        } else {
            cout << "astronauta mais experiente: " << astronautas[maisExperiente].getCpf()
                 << " " << astronautas[maisExperiente].getNome()
                 << " (voos lancados: " << maxVoos << ")" << endl;
        }
        if (taxa == -1){
            cout << "taxa de sucesso: (nenhum voo finalizado)" << endl;
        } else {
            cout << "taxa de sucesso: " << taxa << "%" << endl;
        }
    }

    void mostrarAstronauta(string cpf){
        int posicao = buscarAstronauta(cpf);
        if (posicao == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }

        cout << "CPF: " << astronautas[posicao].getCpf() << endl;
        cout << "Nome: " << astronautas[posicao].getNome() << endl;
        cout << "Idade: " << astronautas[posicao].getIdade() << endl;

        string status;
        if (!astronautas[posicao].estaVivo()){
            status = "morto";
        } else if (!astronautas[posicao].estaDisponivel()){
            status = "vivo e indisponivel";
        } else {
            status = "vivo e disponivel";
        }
        cout << "Status: " << status << endl;
        cout << "Voos lancados: " << astronautas[posicao].getVoosLancados() << endl;
    }

    void estatisticasVoo(int codigo){
        int posicao = buscarVoo(codigo);
        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
            return;
        }

        cout << "Voo " << voos[posicao].getCodigo() << endl;
        cout << "Estado: " << voos[posicao].getEstado() << endl;
        cout << "Astronautas: ";

        if (voos[posicao].getQuantidadeAstronautas() == 0){
            cout << "(nenhum)";
        } else {
            for (int j = 0; j < voos[posicao].getQuantidadeAstronautas(); j++){
                string cpf = voos[posicao].getCpf(j);
                int posicaoA = buscarAstronauta(cpf);
                if (posicaoA == -1) continue;

                if (j > 0) cout << ", ";
                cout << astronautas[posicaoA].getCpf() << " " << astronautas[posicaoA].getNome();
            }
        }
        cout << endl;
    }

    };

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando) {   

        if (comando == "FIM") {
            break;

        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;

            cin >> cpf >> idade;
            getline(cin >> ws, nome);  
            
            agencia.cadastrarAstronauta(cpf, nome, idade);

        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.cadastrarVoo(codigo);
            
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.adicionarAstronauta(cpf, codigo);
            
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;

            agencia.removerAstronauta(cpf, codigo);

        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.lancarVoo(codigo);
            
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.explodirVoo(codigo);
            
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;

            agencia.finalizarVoo(codigo);
           
        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();
            
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();

        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();

        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.historico(cpf);

        } else if (comando == "RELATORIO") {
            agencia.relatorio();

        } else if (comando == "BUSCAR_ASTRONAUTA") {
            string cpf;
            cin >> cpf;
            agencia.mostrarAstronauta(cpf);

        } else if (comando == "ESTATISTICAS_VOO") {
            int codigo;
            cin >> codigo;
            agencia.estatisticasVoo(codigo);

        } else if (comando == "SALVAR") {
            string nome_arquivo;
            cin >> nome_arquivo;
            agencia.salvar(nome_arquivo);

        } else if (comando == "CARREGAR") {
            string nome_arquivo;
            cin >> nome_arquivo;
            agencia.carregar(nome_arquivo);

        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}

