/**
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS
 *
 * File:     Connect.cpp
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
 */
#include "Connect.h"


/**
 * Initializing Library Items
 */
void Connect::initialization() {
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
}

void Connect::initializationSslConnect() {
    ctx = SSL_CTX_new(SSLv23_client_method());
}

/**
 * Loading the default trust certificate
 * @return If the certificate has been loaded it will return true, if not return false
 */
bool Connect::addDefaultSslCertificate() {
    if(!SSL_CTX_set_default_verify_paths(ctx)){
        Error::errorPrint(Error::ERROR_FAIL_DEFAULT_CERTIFICATE);
        return false;
    }
    return true;
}

/**
 * Loading the specified user's trust certificate
 * @return If the certificate has been loaded it will return true, if not return false
 */
bool Connect::addSslCertificate(const std::string& certificatePath) {
    if(!SSL_CTX_load_verify_locations(ctx, certificatePath.c_str(), nullptr)){
        Error::errorPrint(Error::ERROR_FAIL_CERTIFICATE_FILE);
        return false;
    }
    return true;
}

/**
 * Loading the specified user's trust certificate store
 * @return If the certificate has been loaded it will return true, if not return false
 */
bool Connect::addSslCertificateDir(const std::string& certificateDirPath) {
    if(!SSL_CTX_load_verify_locations(ctx, nullptr, certificateDirPath.c_str())){
        Error::errorPrint(Error::ERROR_FAIL_CERTIFICATE_DIR);
        return false;
    }
    return true;
}

/**
 * Loading the specified user's trust certificate store
 * @return If the certificate has been loaded it will return true, if not return false
 */
bool Connect::addSslCertificateAndDir(const std::string& certificatePath, const std::string& certificateDirPath) {
    if(!SSL_CTX_load_verify_locations(ctx, certificatePath.c_str(), certificateDirPath.c_str())){
        Error::errorPrint(Error::ERROR_FAIL_CERTIFICATE_DIR);
        return false;
    }
    return true;
}

/**
 * Setting up the BIO object
 * @return true on success false on Setting up failure
 */
bool Connect::settingBio() {
    bio = BIO_new_ssl_connect(ctx);
    if(!bio){
        Error::errorPrint(Error::ERROR_SSL_CONNECTION_FAIL);
        return false;
    }
    BIO_get_ssl(bio, &ssl);
    //set flag for automatic handshake if server suddenly wants a new handshake
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    return true;
}

/**
 * Opening a insecure connection
 * @param url
 * @return true if connection succeeds false if connection fails
 */
bool Connect::insecureConnect(const std::string& url){
    bio = BIO_new_connect(url.c_str());
    if(bio == nullptr)
    {
        Error::errorPrint(Error::ERROR_FAIL_CREATE_BIO);
        return false;
    }
    return true;
}

/**
 * Checks if the connection succeeded.
 * @return true if connection succeeds false if connection fails
 */
bool Connect::checkConnect(){
    if(BIO_do_connect(bio) <= 0)
    {
//        printf("%s\n", ERR_error_string(ERR_get_error(), NULL));
        Error::errorPrint(Error::ERROR_FAIL_OPEN_CONNECT);
        return false;
    }
    return true;
}
/**
 * Opening a secure connection
 * @param url URL-address:port
 */
bool Connect::sslConnect(const std::string& url, const std::string& host) {
    if(!SSL_set_tlsext_host_name(ssl,host.c_str())){
        Error::errorPrint(Error::ERROR_SSL);
        return false;
    }
    BIO_set_conn_hostname(bio, url.c_str());

    return true;
}

/**
 * Checks the validity of the certificate
 * @return true if certificate is valid false if certificate is invalid
 */
bool Connect::isCertificateValid() {
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        Error::errorPrint(Error::ERROR_CERTIFICATE_INVALID);
        return false;
    }

    return true;
}

/**
 * Send request to server
 * @param request request string
 * @return success
 */
bool Connect::sendRequest(const std::string& request) {
    bool success = false;
    //if the request is not sent, and it will be possible to resend, then the request will be sent again
    do{
        if(BIO_write(bio, request.c_str(), request.length()) > 0){
            success = true;
        }
    }while(!success && BIO_should_retry(bio));

    if(!success){
        Error::errorPrint(Error::ERROR_SEND_REQUEST);
    }
    return success;

}

/**
 * Receives a response from the server and writes to the buffer
 * @param response
 * @return
 */
bool Connect::readResponse(std::string &response) {
    bool success = false;
    bool error = false;
    int readBytes = 0;
    char buffer[BUFFER_SIZE] = {'\0'};

    //Loop read the response from the server
    //If an error occur, and it is possible to repeat the reading, repeat
    do{
        readBytes = BIO_read(bio, buffer, BUFFER_SIZE - 1);

        if(readBytes > 0){
            buffer[readBytes] = '\0';
            response += buffer;
        }else if(readBytes < 0){
            success = false;
            if(!BIO_should_retry(bio)){
                error = true;
            }
        }else{
            success = true;
        }

    }while(!success && !error);

    if(error){
        Error::errorPrint(Error::ERROR_READ_BIO);
    }

    return success;
}

/**
 * Close connection and reset structure for next connection
 */
void Connect::closeConnect() {

    if(bio){
        BIO_free_all(bio);
    }
    if(ctx){
        SSL_CTX_free(ctx);
    }
    bio = nullptr;
    ctx = nullptr;
}

void Connect::fullExit() {
//    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
}