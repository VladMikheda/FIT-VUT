IJA 2021–2022 (Úkol 3)
Vedoucí týmu: Vladislav Mikheda : xmikhe00
Člen týmu: Anvar Kilybayev : xkilyb00

Akce:
    před kompilaci je nutné spustit skript v direktore lib

    Kompilace:
        mvn compile

    Vygenerovaní dokumentace:
        javadoc -private -splitindex -use -author -version -nodeprecatedlist -d doc -classpath "lib/*" "src/main/java/ija/diagram/classdiagram/view/ViewDiagram.java" "src/main/java/ija/diagram/classdiagram/controller/ControllerMain.java" "src/main/java/ija/diagram/classdiagram/view/ViewClass.java" "src/main/java/ija/diagram/loader/Loader.java" "src/main/java/ija/diagram/classdiagram/model/Relationships.java" "src/main/java/ija/diagram/classdiagram/model/DClass.java" "src/main/java/ija/diagram/classdiagram/controller/ViewClassController.java" "src/main/java/ija/diagram/loader/Parser.java" "src/main/java/ija/diagram/loader/objectJSON.java" "src/main/java/ija/diagram/Main.java" "src/main/java/ija/diagram/loader/attrJSON.java" "src/main/java/ija/diagram/classdiagram/controller/ClassContextController.java" "src/main/java/ija/diagram/classdiagram/model/Arguments.java" "src/main/java/ija/diagram/classdiagram/model/ClassDiagram.java" "src/main/java/ija/diagram/classdiagram/model/Element.java" "src/main/java/ija/diagram/classdiagram/model/Item.java" "src/main/java/ija/diagram/classdiagram/model/Methods.java" "src/main/java/ija/diagram/classdiagram/view/ArgumentItem.java" "src/main/java/ija/diagram/classdiagram/view/MethodItem.java" "src/main/java/ija/diagram/classdiagram/view/ViewItem.java" "src/main/java/ija/diagram/loader/Writer.java"

    Vytvoření jar souboru:
        mvn package

    Spuštění:
        java  --module-path lib/javafx-sdk-18/lib  --add-modules=javafx.controls,javafx.fxml -jar dest/ija-app.jar

Popis:
    Po spuštění v okně jsou 3 tlačítka:
        "Add" - přidává novou třídu která bude automaticky pojmenovaná pořadovým číslem
        "Load" - načte soubor a přidá třídy do okénka. Načítá jen soubor který se jmenuje "input.json" a nachází se v adresáře "data"
        "Save" - uloží třídy do souboru "output.json" v adresáře "data". Vztahy nebudou uloženy a  také nebudou uloženy názvy argumentu a metod které byly dopsané uživatelem

    Třídy lze hýbat po okénku, děla se to pomocí středního tlačítka myši, je nutné jej vytlačit a pohybovat myší.
    Do třídy lze přidat argumenty a metody, třídu lze také vymazat proto je nutné využit kontextovou nabídku, pro její otevírání je nutné vytlačit pravé tlačítko myši v levém horním uhlu třídy:
    "Add new argument" - dodává nový argument do třídy
    "Add new method" -  dodává novou metodu do třídy
    "Delete class" - vymaže třídu

    Metody a argumenty je možné vymazat pomocí spouštění kontextové nabídky, pro její otevírání je nutné vytlačit pravé tlačítko myši na metodě nebo třídě:
        "Delete" - vymaže metodu nebo třídu
