# -*- coding: utf-8 -*-

# lettura del chilometraggio totale
def Leggi(inizio,blocchi,lettura):
    valore = 0
    lettura.seek(inizio)
    for x in range(blocchi):
        lett = lettura.read(1)
        lett = ord(lett) # ord() converte da stringa Unicode a int
        valore += lett*(10**x)
    return valore
    
# scrittura del nuovo chilometraggio totale
def Scrivi(inizio,blocchi,chilometri_nuovo,out):
    valore = 0
    km = chilometri_nuovo
    out.seek(inizio)
    for x in range(blocchi):
        valore = km % 10
        valore = chr(valore)
        out.write(valore)
        km /= 10
   
inizio = 0x1C # primo byte (più significativo) odometro totale
blocchi = 6 # numero totale di byte adibiti al chilometraggio 
in_file = raw_input("inserisci il nome del file da modificare: ")
lettura = open(in_file,'rb')
out = open("out",'wb')
chilometri_nuovo = int(raw_input("inserisci il nuovo numero di chilometri: "))

# copio il file originale
while (True):
    cp = lettura.read(1)
    if cp == '':
        break
    out.write(cp)
 
print( "Valore attuale: %d" % Leggi(inizio,blocchi,lettura))
# modifico nel nuovo file il contenuto dei blocchi dell'odometro totale
Scrivi(inizio,blocchi,chilometri_nuovo,out)

lettura.close()
out.close()

controllo = open("out",'rb')
print("Nuovo valore: %d" % Leggi(inizio,blocchi,controllo))
controllo.close()

