//algoritmos

#include <iostream>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>

void popularVetorCrescente(long double *ptr, int tamanho);
void popularVetorDecrescente(long double *ptr, int tamanho);
void popularVetorAleatorio(long double *ptr, int tamanho);
void imprimirVetor(long double *ptr, int tamanho);
void trocar(void *A, void *B, size_t t);
void insertionSort(long double *ptr, int tamanho);
void selectionSort(long double *ptr, int tamanho);
void bubbleSort(long double *ptr, int tamanho);
void mergeSort(long double *ptr, int p, int r);
void merge(long double *ptr, int p, int q, int r);
void heapSort(long double *ptr, int tamanho);
void buildMaxHeap(long double *ptr, int tamanho, int& tamanhoDoHeap);
void maxHeapify(long double *ptr, int i, int& tamanhoDoHeap);
void quickSort(long double *ptr, int p, int r);
int partition(long double *ptr, int p, int r);
bool comparar(void *A, void *B, int tamanho, size_t t);
void insertionSortGenerico(void *ptr, int tamanho, size_t t);

void popularVetorCrescente(long double *ptr, int tamanho){
    for (int x = 0; x < tamanho; x++)
        *(ptr + x) = x;    
}

void popularVetorDecrescente(long double *ptr, int tamanho){
    for (int x = 0, y = tamanho - 1; x < tamanho && y >= 0; x++, y--)
        *(ptr + x) = y;    
}

void popularVetorAleatorio(long double *ptr, int tamanho){
    srand(time(0));
    for (int x = 0; x < tamanho; x++)
        *(ptr + x) = rand()/((rand() % 99) + 1);
}

void imprimirVetor(long double *ptr, int tamanho){
    for (int x = 0; x < tamanho; x++)
        std::cout<<*(ptr + x) <<"\n";
}

int main(){
    long int tamanho = 100;
    long double *vetor1 = new long double[tamanho];
    long double *vetor2 = new long double[tamanho];
    long double *vetor3 = new long double[tamanho];
    long double *vetor4 = new long double[tamanho];
    popularVetorCrescente(vetor1, tamanho);
    popularVetorCrescente(vetor2, tamanho);
    popularVetorCrescente(vetor3, tamanho);
    popularVetorCrescente(vetor4, tamanho);
    void(*funcPtr1)(long double *ptr, int tamanho) = insertionSort;
    void(*funcPtr2)(long double *ptr, int tamanho) = selectionSort;
    void(*funcPtr3)(long double *ptr, int tamanho) = bubbleSort;
    void(*funcPtr4)(long double *ptr, int tamanho) = heapSort;

    std::cout<<"VETORES NO MELHOR CASO: \n";
    std::thread thread1 (funcPtr1, vetor1, tamanho);
    std::thread thread2 (funcPtr2, vetor2, tamanho);
    std::thread thread3 (funcPtr3, vetor3, tamanho);
    std::thread thread4 (funcPtr4, vetor4, tamanho);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    popularVetorAleatorio(vetor1, tamanho);
    popularVetorAleatorio(vetor2, tamanho);
    popularVetorAleatorio(vetor3, tamanho);
    popularVetorAleatorio(vetor4, tamanho);


    std::cout<<"\n\nVETORES NO CASO MEDIO: \n";
    std::thread thread5 (funcPtr1, vetor1, tamanho);
    std::thread thread6 (funcPtr2, vetor2, tamanho);
    std::thread thread7 (funcPtr3, vetor3, tamanho);
    std::thread thread8 (funcPtr4, vetor4, tamanho);

    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();

    popularVetorDecrescente(vetor1, tamanho);
    popularVetorDecrescente(vetor2, tamanho);
    popularVetorDecrescente(vetor3, tamanho);
    popularVetorDecrescente(vetor4, tamanho);

    std::cout<<"\n\nVETORES NO PIOR CASO: \n";
    std::thread thread9 (funcPtr1, vetor1, tamanho);
    std::thread thread10 (funcPtr2, vetor2, tamanho);
    std::thread thread11 (funcPtr3, vetor3, tamanho);
    std::thread thread12 (funcPtr4, vetor4, tamanho);

    thread9.join();
    thread10.join();
    thread11.join();
    thread12.join();




    delete []vetor1;
    delete []vetor2;
    delete []vetor3;
    delete []vetor4;
}


void trocar(void *A, void *B, size_t t){
    char *c = static_cast<char*>(A);
    char *d = static_cast<char*>(B);
    char e = 0;
    for (int x = 0; x < static_cast<int>(t); x++){
        e = *(c + x); //E = A
        *(c + x) = *(d + x); //A = B
        *(d + x) = e; //B = E = A
    }
}

void insertionSort(long double *ptr, int tamanho){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    long double chave = 0;
    int i = 0;
    for (int j = 1; j < tamanho; j++){
        chave = *(ptr + j);
        i = j - 1;
        while(i >= 0 && chave < *(ptr + i)){
            *(ptr + i + 1) = *(ptr + i);
            i--;
            *(ptr + i + 1) = chave;
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    std::cout<<"INSERTION SORTED IN " <<duration <<" seconds!" <<std::endl;
}

void selectionSort(long double *ptr, int tamanho){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int i = 0;
    long double aux = 0;
    for (int j = 0; j < tamanho - 1; j++){
        i = j + 1;
        while (i < tamanho){
            if (*(ptr + j) > *(ptr + i)){
                aux = *(ptr + i);
                *(ptr + i) = *(ptr + j);
                *(ptr + j) = aux;
            }
            i++;
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    std::cout<<"SELECTION SORTED IN " <<duration <<" seconds!" <<std::endl;
}

void bubbleSort(long double *ptr, int tamanho){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    long double aux = 0;
    for (int i = 0; i < tamanho; i++){
        for (int k = tamanho - 1; k >= i + 1; k--){
            if (*(ptr + k) < *(ptr + k - 1)){
                aux = *(ptr + k);
                *(ptr + k) = *(ptr + k - 1);
                *(ptr + k - 1) = aux;
            }
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    std::cout<<"BUBBLE SORTED IN " <<duration <<" seconds!" <<std::endl;
}

void mergeSort(long double *ptr, int p, int r){
    if (p < r){
        int q = (p + r)/2;
        mergeSort(ptr, p, q);
        mergeSort(ptr, q + 1, r);
        merge(ptr, p, q, r);
    }
}

void merge(long double *ptr, int p, int q, int r){
    int nL = q - p + 1;
    int nR = r - q;
    long double *L = new long double[nL];
    long double *R = new long double[nR];
    for (int i = 0; i < nL; i++)
        *(L + i) = *(ptr + p + i);
    for (int j = 0; j < nR; j++)
        *(R + j) = *(ptr + q + 1 + j);

    int i = 0;
    int j = 0;
    int k = p;

    while(i < nL && j < nR){
        if (*(L + i) <= *(R + j)){
            *(ptr + k) = *(L + i);
            i++;
        }

        else{
            *(ptr + k) = *(R + j);
            j++;
        }

        k++;
    }

    while (i < nL){
        *(ptr + k) = *(L + i);
        i++;
        k++;
    }

    while (j < nR){
        *(ptr + k) = *(R + j);
        j++;
        k++;
    }

    delete []L;
    delete []R;
}

void heapSort(long double *ptr, int tamanho){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int tamanhoDoHeap = 0;
    buildMaxHeap(ptr, tamanho, tamanhoDoHeap);
    for (int i = tamanhoDoHeap - 1; i > 0; i--){
        trocar((ptr + i), (ptr), sizeof (*ptr));
        tamanhoDoHeap--;
        maxHeapify(ptr, 0, tamanhoDoHeap);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();
    std::cout<<"HEAP SORTED IN " <<duration <<" seconds!" <<std::endl;
}

void buildMaxHeap(long double *ptr, int tamanho, int& tamanhoDoHeap){
    tamanhoDoHeap = tamanho;
    for (int i = (tamanhoDoHeap/2) - 1; i >= 0; i--)
        maxHeapify(ptr, i, tamanhoDoHeap);
}

void maxHeapify(long double *ptr, int i, int& tamanhoDoHeap){
    int L = 2 * i + 1;
    int R = L + 1;
    int maior = i;
    if (L < tamanhoDoHeap && *(ptr + L) > *(ptr + maior))
        maior = L;
    if (R < tamanhoDoHeap && *(ptr + R) > *(ptr + maior))
        maior = R;

    if (i != maior){
        trocar((ptr + i), (ptr + maior), sizeof (*ptr));
        maxHeapify(ptr, maior, tamanhoDoHeap);
    }
}


void quickSort(long double *ptr, int p, int r){
    if (p < r){
        int q = partition(ptr, p,r);
        quickSort(ptr, p, q - 1);
        quickSort(ptr, q + 1, r);
    }
}

int partition(long double *ptr, int p, int r){
    long double pivo = *(ptr + r);
    int i = p - 1;
    for (int j = p; j <= r - 1; j++){
        if (*(ptr + j) <= pivo){
            i++;
            trocar((ptr + j), (ptr + i), sizeof (*ptr));
        }
    }
    trocar((ptr + i + 1), (ptr + r), sizeof (*ptr));
    return i + 1;
}

void insertionSortGenerico(void *ptr, int tamanho, size_t t){
    char *c = static_cast<char*>(ptr);
    char *chave = new char[t];
    int aux = 0;
    int i = 0;
    for (int j = 1; j < tamanho; j++){
        for (int k = 0; k < static_cast<int>(t); k++)
            *(chave + k) = static_cast<char>(*(c + k + (j * static_cast<int>(t))));
        i = j - 1;
        aux = 1;
        while (i >= 0 && *(chave) < *(c + aux + (i * static_cast<int>(t)))){
            for (int l = 0; l < static_cast<int>(t); l++)
                *(c + l + ((i * static_cast<int>(t)) + 1)) = *(c + l + (i * static_cast<int>(t) + 1));
            i--;
            for (int l = 0; l < static_cast<int>(t); l++)
                *(c + l + ((i * static_cast<int>(t)) + 1)) = *(chave + l);
            aux++;
        }
    }
    delete[] chave;
}
