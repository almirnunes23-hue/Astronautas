#include <iostream>
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

public:

    Astronauta(string c, string n, int i){

        cpf = c;
        nome = n;
        idade = i;
        vivo = true;
        disponivel = true;
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
            cout << "OK: astronauta " << cpf << "adicionado ao voo " << codigo << endl;
        }
    }

    void removerAstronauta(string cpf, int codigo){
        int posicaoV = buscarVoo(codigo);

        if (buscarAstronauta(cpf) == -1){
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
            cout << "OK: astronauta " << cpf << "removido do voo " << codigo << endl;
        }
    }

    void lancarVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicao].getEstado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        }
        else if(voos[posicao].getQuantidadeAstronautas() <= 0){
            cout << "ERRO: voo " << codigo << " nao tem astronautas" << endl;
        }
        for (int i = 0; i < voos[posicao].getQuantidadeAstronautas(); i++){
            string cpf = voos[posicao].getCpf(i);
            int posicaoA = buscarAstronauta(cpf);

            if (astronautas[posicaoA].estaDisponivel() == false){
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
            else if (astronautas[posicaoA].estaVivo() == false){
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }
        }
        voos[posicao].lancar();
        cout << "OK: voo " << codigo << " foi lancado" << endl;
    }

    void explodirVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicao].getEstado() != "em curso"){
            cout << "ERRO: voo " << codigo << " nao em curso" << endl;
        }
        else{
            voos[posicao].explodir();
            cout << "OK: voo " << codigo << " explodiu" << endl;
        }
    }

    void finalizarVoo(int codigo){
        int posicao = buscarVoo(codigo);

        if (posicao == -1){
            cout << "ERRO: Voo " << codigo << " nao cadastrado" << endl;
        }
        else if(voos[posicao].getEstado() != "em curso"){
            cout << "ERRO: voo " << codigo << " nao em curso" << endl;
        }
        else{
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
            
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}

