import threading

class ScrieText(threading.Thread):
    def __init__(self, texte, output):
        threading.Thread.__init__(self)
        self.texte = texte
        self.output = output

    def run(self):
        while self.texte:
            text = self.texte.pop()
            sir=""
            for i in range(1000):
                sir = str(i) + " " +str (text)+"\n"
                self.output.write(sir)
            print('write %s done by %s' % (text, self.name))
def main():
    texte1=['text1', 'text2']
    texte2=['text3', 'text4']
    f = open('output_ex1.txt', 'w+')
    t1= ScrieText(texte1, f)
    t2=ScrieText(texte2, f)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    f.close()
if __name__ == '__main__':
    main()            
