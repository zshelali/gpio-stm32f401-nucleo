# Ali Hajeri - SY41 - IDE : STM32CubeIDE

## Pour lancer le projet :

* Simplement importer le dossier STM32F401. S'il ne compile pas ou qu'il ne fonctionne pas, remplacer le main.c par main_backup.c et le renommer en "main.c"


### fichiers :

- main_backup.c : dernier fichier main fonctionnel et testé. À mettre dans le fichier src du projet si le fichier principal ne compile pas
 
- main_modifie.c : fichier main principal. normalement fonctionne, mais non testé après l'ajout des commentaires. Il est possible qu'une erreur se soit glissée.

-STM32F401 : dossier du projet. Pour son main.c, il a le code du fichier main_modifie.c s'il ne compile pas, le dernier code testé et fonctionnel avant l'ajout des commentaires est main_backup.c  


