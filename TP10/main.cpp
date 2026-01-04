int main(){
    // - Déclaration
    mat grid;
    size_t KMatSize;
    unsigned KNbCandies;

    maPosition pos;

    clearScreen();
    loadingScreen();

    InputManager input;
    input.enableRawMode();

    bool loadingScreen = true;

    unsigned select = 0;

    char c;
    while (cin.get(c) && c!=27){
            if (loadingScreen){
                if (c == 10){
                    displayMenu(select);
                    loadingScreen = false;
                }
            }
            else{
                if (c==10) break;
                moveMenu(c,select);
                displayMenu(select);
            }
    }
    Joueur j;
    if (select == 0) {
        j =classicMode(grid, KMatSize, KNbCandies, pos);
        ajouter_score("classic" , j.nom, j.score);
    }
    //else if (select == 1) {duelMode(grid, KMatSize, KNbCandies, pos);}
    else if (select == 2) {
        string mode;
        cout << "Quel mode de jeu (classic, duel, endless) ? : ";
        cin >> mode;
        vector<Joueur> lb = lire_score( mode);
        tri_score(lb);
        if (lb.size()<10){
            for (size_t i=0; i<lb.size(); ++i){
                cout << lb[i].nom << " : " << lb[i].score << endl;
            }
        } else {
            for (size_t i=0; i<10; ++i){
                cout << lb[i].nom << " : " << lb[i].score << endl;
            }
        }
        
    }
    else if (select == 3){
        j=endlessMode(grid, KMatSize, KNbCandies, pos);
        ajouter_score("endless", j.nom, j.score);
    }
    
    

    input.disableRawMode();
    return 0;
}
