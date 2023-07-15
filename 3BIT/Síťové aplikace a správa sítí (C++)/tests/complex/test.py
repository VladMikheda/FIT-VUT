"""
 * Project: Čtečka novinek ve formátu Atom a RSS s podporou TLS (Tests)
 *
 * File:     test.py
 * Subject:  ISA 2022
 *
 * @author:  Vladislav Mikheda  xmikhe00
"""

"""
Script for complex testing of the whole program
"""
import os
import sys
import subprocess

main_path = "cd ../../;"
cert_dir_path = " -C '/etc/ssl/certs' "
cert = " -c '/etc/ssl/certs/ISRG_Root_X1.pem' "

def compiling():
    result = subprocess.run([ main_path+"make"], stdout=subprocess.PIPE, encoding='utf-8', shell=True)
    assert (result.returncode == 0)


def normal_url():
    result = subprocess.run([main_path+" ./feedreader 'https://www.rssboard.org/files/sample-rss-2.xml'"],
                            stdout=subprocess.PIPE, shell=True)
    expect_result = b"*** Liftoff News ***\nStar City\nThe Engine That Does More\nAstronauts' Dirty Laundry\n"
    assert (result.stdout == expect_result)
    print("Normal url test success")


def all_arguments():
    result = subprocess.run([main_path+"./feedreader 'https://www.rssboard.org/files/sample-rss-2.xml' -a -u -T"],
                            stdout=subprocess.PIPE, shell=True)
    expect_result = b"*** Liftoff News ***\nStar City\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-starcity.asp\nZverejneno: Tue, 03 Jun 2003 09:39:21 GMT\n\n----\nZverejneno: Fri, 30 May 2003 11:06:42 GMT\n\nThe Engine That Does More\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-VASIMR.asp\nZverejneno: Tue, 27 May 2003 08:37:32 GMT\n\nAstronauts' Dirty Laundry\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-laundry.asp\nZverejneno: Tue, 20 May 2003 08:56:02 GMT\n"
    # print(result.stdout)
    assert (result.stdout == expect_result)
    print("All arguments test success")


def cert_dir():
    result = subprocess.run(
        [main_path+" ./feedreader 'https://www.rssboard.org/files/sample-rss-2.xml' " +cert_dir_path + " -a -u -T"],
        stdout=subprocess.PIPE, shell=True)
    expect_result = b"*** Liftoff News ***\nStar City\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-starcity.asp\nZverejneno: Tue, 03 Jun 2003 09:39:21 GMT\n\n----\nZverejneno: Fri, 30 May 2003 11:06:42 GMT\n\nThe Engine That Does More\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-VASIMR.asp\nZverejneno: Tue, 27 May 2003 08:37:32 GMT\n\nAstronauts' Dirty Laundry\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-laundry.asp\nZverejneno: Tue, 20 May 2003 08:56:02 GMT\n"
    assert (result.stdout == expect_result)
    print("Certificate dir test success")


def cert_file_and_dir():
    result = subprocess.run(
        [
            main_path+" ./feedreader 'https://www.rssboard.org/files/sample-rss-2.xml' " + cert_dir_path + cert + " -a -u -T"],
        stdout=subprocess.PIPE, shell=True)
    expect_result = b"*** Liftoff News ***\nStar City\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-starcity.asp\nZverejneno: Tue, 03 Jun 2003 09:39:21 GMT\n\n----\nZverejneno: Fri, 30 May 2003 11:06:42 GMT\n\nThe Engine That Does More\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-VASIMR.asp\nZverejneno: Tue, 27 May 2003 08:37:32 GMT\n\nAstronauts' Dirty Laundry\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-laundry.asp\nZverejneno: Tue, 20 May 2003 08:56:02 GMT\n"
    assert (result.stdout == expect_result)
    print("Certificate file and dir test success")


def cert_file():
    result = subprocess.run(
        [
            main_path+" ./feedreader 'https://www.rssboard.org/files/sample-rss-2.xml' "+ cert + " -a -u -T"],
        stdout=subprocess.PIPE, shell=True)
    expect_result = b"*** Liftoff News ***\nStar City\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-starcity.asp\nZverejneno: Tue, 03 Jun 2003 09:39:21 GMT\n\n----\nZverejneno: Fri, 30 May 2003 11:06:42 GMT\n\nThe Engine That Does More\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-VASIMR.asp\nZverejneno: Tue, 27 May 2003 08:37:32 GMT\n\nAstronauts' Dirty Laundry\nURL: http://liftoff.msfc.nasa.gov/news/2003/news-laundry.asp\nZverejneno: Tue, 20 May 2003 08:56:02 GMT\n"
    assert (result.stdout == expect_result)
    print("Certificate file test success")


def atom_file():
    result = subprocess.run([main_path+"./feedreader 'https://xkcd.com/atom.xml' -a -u -T"], stdout=subprocess.PIPE,
                            shell=True)
    expect_result_code = b'*** xkcd.com ***\nK\xc3\xb6nigsberg\nURL: https://xkcd.com/2694/\nAktualizace: 2022-11-04T00:00:00Z\n\nWirecutter Recommendation\nURL: https://xkcd.com/2693/\nAktualizace: 2022-11-02T00:00:00Z\n\nInterior Decorating\nURL: https://xkcd.com/2692/\nAktualizace: 2022-10-31T00:00:00Z\n\nEncryption\nURL: https://xkcd.com/2691/\nAktualizace: 2022-10-28T00:00:00Z\n'
    if (expect_result_code == result.stdout):
        print("Atom test success")
    else:
        print("\033[0m", end="")
        print("Atom test failed, perhaps the data on the site has been updated")
        print("\033[32m", end="")


def feed_list_test():
    result = subprocess.run(
        [
            main_path+" ./feedreader -f 'tests/feedlist' -a -u -T"], stdout=subprocess.PIPE,
        shell=True)
    expected_return_code = 0
    assert (result.returncode == expected_return_code)
    print("Feed list test success")


if __name__ == '__main__':
    if len(sys.argv) > 1:
        main_path = sys.argv[1]
        if len(sys.argv) > 2:
            if(sys.argv[2] == "nocert"):
                cert_dir_path = ""
                cert = ""
    # compiling()
    print("Tests all:")
    print("\033[32m", end="")
    normal_url()
    all_arguments()
    cert_dir()
    cert_file()
    cert_file_and_dir()
    atom_file()
    feed_list_test()
    print("\033[0m", end="")
