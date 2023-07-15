/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     Error.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */

#include "Error.h"

/**
 * Print error
 * @param errorNumber
 * @param ex whether the program should end after writing out the error
 */
void Error::errorPrint(int errorNumber) {
    bool help = false;
    std::string errorMessage{0};
    std::cerr << "\n" <<"Chyba : " ;
    switch (errorNumber) {
        case ERROR_ARGUMENT_NOT_EXIST:
            errorMessage = "Zadaný argument neexistuje";
            help = true;
            break;
        case ERROR_ARGUMENT_NOT_VALUE:
            errorMessage = "Za argumentem musí následovat hodnota argumentu";
            help = true;
            break;
        case ERROR_URL_OR_FEED_FILE:
            errorMessage = "Musí být zadána adresa URL nebo feed file";
            help = true;
            break;
        case ERROR_FAIL_DEFAULT_CERTIFICATE:
            errorMessage = "Problém se standardním certifikátem";
            break;
        case ERROR_FAIL_CERTIFICATE_FILE:
            errorMessage = "Problém se souborem certifikátu";
            break;
        case ERROR_FAIL_CERTIFICATE_DIR:
            errorMessage = "Problém s adresáři certifikátů";
            break;
        case ERROR_FAIL_OPEN_SECURE_CONNECT:
            errorMessage = "Nepodařilo se otevřít připojení SSL";
            break;
        case ERROR_FAIL_OPEN_CONNECT:
            errorMessage = "Failed to open connection";
            break;
        case ERROR_FAIL_CREATE_BIO:
            errorMessage = "Připojení se nezdařilo otevřít";
            break;
        case ERROR_CERTIFICATE_INVALID:
            errorMessage = "Používaný certifikát je neplatný";
            break;
        case ERROR_SSL_CONNECTION_FAIL:
            errorMessage = "Připojení se nezdařilo";
            break;
        case ERROR_SEND_REQUEST:
            errorMessage = "Chyba odeslání požadavku";
            break;
        case ERROR_READ_BIO:
            errorMessage = "Odpověď serveru nelze přečíst";
            break;
        case ERROR_ARGUMENT_REPEAT:
            errorMessage = "Použití duplicitních argumentů";
            help = true;
            break;
        case ERROR_URL_INVALID:
            errorMessage = "Zadaná adresa URL je nesprávná";
            break;
        case ERROR_PORT_INVALID:
            errorMessage = "Zadaný port je neplatný";
            break;
        case ERROR_NOT_OPEN_XML_DOC:
            errorMessage = "Nelze otevřít XML";
            break;
        case ERROR_NOT_EXIST_ROOT_ELEMENT:
            errorMessage = "Hlavní kořen dokumentu XML nebyl vložen";
            break;
        case ERROR_NOT_SUPPORTED_FORMAT:
            errorMessage = "Soubor XML je ve formátu, který není podporován";
            break;
        case ERROR_NOT_SUPPORTED_RSS_VERSION:
            errorMessage = "Verze RSS není podporována";
            break;
        case ERROR_NOT_CORRECT_RESPONSE:
            errorMessage = "Kód odpovědi ze serveru není úspěšný";
            break;
        case ERROR_RESPONSE_HAS_NO_BODY:
            errorMessage = "Odpověď ze serveru neobsahuje tělo";
            break;
        case ERROR_NOT_OPEN_FILE:
            errorMessage = "Nelze otevřít soubor zdroje";
            break;
        case ERROR_SSL:
            errorMessage = "SSL error";
            break;
        default:
            errorMessage = "";
            break;
    }

    std::cerr << errorMessage << std::endl;
    if(help){
        helpOut();
    }
}

/**
 * Print message on std error
 * @param message text message
 */
void Error::printMessage(std::string message) {
    std::cerr << message << std::endl;
}

void Error::exitProgram(int exitNumber) {
    std::exit(exitNumber);
}

void Error::helpOut() {

    std::string message = std::string("\n./feadreader <url adresa | -f <feedfile>> [-c <certfile>] [-C <certaddr>] [-T] [-a] [-u]\n")
           + "url adresa zdroje z kterého bude přijata informace pro výstup programu.\n"
           + "-f <feedfile> cesta do souboru feedfile. Soubor musí obsahovat v sobě jednotlivé zdroje, každý zdroj na jednom řádku, takže je možnost komentářů, řádek s komentářem musí se začínat #\n"
           +  "-c <certfile> cesta do certifikátu který bude využít pro ověřování serveru.\n"
           +  "-C <certaddr> cesta do úložiště certifikátů, které bude možné použit pro ověřování serveru\n"
           +  "-T pro každý záznam se zobrazí čas publikovaní nebo čas změny\n"
           +  "-a pro každý záznam se zobrazí autor\n"
           +  "-u pro každý záznam se zobrazí asociované url"
           +  "-h vypíše návod na použití programu";

    std::cerr << message << std::endl;
}
