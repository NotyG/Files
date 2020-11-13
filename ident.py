from tkinter import *
from tkinter.ttk import Combobox as cb
from tkinter import messagebox as mb
from time import sleep as delay

Id = dict(
    z = 'Не это',
    Выберите = 'Не это',
    Дубова_Ирина_Александровна='308-852 3852',
    Кондрашева_Юлия_Александровна='424-733-9234', #1.1
    Чекмарева_Галина_Николаевна='657-634-5656',
    Юлдашева_Лидия_Кашафовна='232-998-1449',
    Кучкарова_Ольга_Расилевна='616-037-5554',
    Земцов_Артем_Валерьевич='818-268-2125',
    Громова_Светлана_Анатольевна='567-082-8527',
    Зайнуллина_Мадина_Ахатовна='782-171-5612',
    Осипова_Валентина_Васильевна='296-689-8344',
    Мухаметзянова_Албина_Табрисовна = '444 958 0995',
    Полякова_Анна_Николаевна='391-792-7881',
    Перцева_Аида_Ансаровна='376-363-5643',
    Савина_Екатерина_Владимировна='431-529-1011',
    Савина_Наталья_Николаевна='503-694-5582',
    Субаева_Ольга_Майковна='398-933-4315',
    Филиппова_Мария_Викторовна='240-562-0776',
    Степанов='4779437462',
    Ахмедьянова='768-610-94-89',
    x = 'Не это'
)
password = dict(
    z='Не это',
    Выберите = 'Не это',
    Дубова_Ирина_Александровна = '576090',
    Кондрашева_Юлия_Александровна='922997',
    Чекмарева_Галина_Николаевна = '006418',
    Юлдашева_Лидия_Кашафовна = '693427',
    Кучкарова_Ольга_Расилевна='770859',
    Земцов_Артем_Валерьевич = '513192',
    Громова_Светлана_Анатольевна = '18923',
    Зайнуллина_Мадина_Ахатовна = '5612',
    Осипова_Валентина_Васильевна = '212225',
    Мухаметзянова_Албина_Табрисовна = 'Albina2020',
    Полякова_Анна_Николаевна = '270969',
    Перцева_Аида_Ансаровна = '882065',
    Савина_Екатерина_Владимировна = '111',
    Савина_Наталья_Николаевна = '555',
    Субаева_Ольга_Майковна = '588407',
    Филиппова_Мария_Викторовна = '090857',
    Степанов = '5K1yzU',
    Ахмедьянова='68',
    x = 'Не это'
)
txt = None
txt2 = None

def clicked():
    global txt
    global txt2
    keyEnt = ent.get();
    keyCb =  combo.get();
    if(keyEnt and keyEnt.strip()):
        keyEnt = keyEnt.replace(" ", "_")
        txt = Id.get(keyEnt); #id
        txt2 = password.get(keyEnt)  #passw
        #lblt.configure(text = keyEnt)
    else:
        if keyCb == "'x'])" or keyCb == "dict_keys(['z',":   #1.1
            keyCb = 'Выберите'                               #1.1
        keyCb = keyCb.replace("'", "")
        keyCb = keyCb.replace(",", "")
        txt = Id.get(keyCb); #id
        txt2 = password.get(keyCb)#passw
        #lblt.configure(text = keyCb)
    lbl3.configure(text = txt);
    lbl4.configure(text = txt2)


def copy():
    clip = Tk()
    clip.withdraw()
    clip.clipboard_clear()
    clip.clipboard_append(txt)
    clip.destroy()

def copy2():
    clip = Tk()
    clip.withdraw()
    clip.clipboard_clear()
    clip.clipboard_append(txt2)
    clip.destroy()

def name(): #2
    ans = mb.askokcancel('Подверждаю', 'Программу сделали Глеб Чекмарев и Вадим Гнездилов в 2020')
    if ans == False:
        mb.showinfo('', 'Как вы нашли эту кнопку?')
        ans1 = mb.askyesno('', 'Вы что специально тыкали по окну?')
        if ans1 == True:
            mb.showinfo('', 'Зачем? Хотя это ваше дело')
            mb.showinfo('Пожалуйста', 'Раз вы уже вышли к этому окну то, пожалуйста поставьте нам пятёрки')
        if ans1 == False:
            mb.showinfo('', 'Значит вам крупно повезло')
            mb.showinfo('Пожалуйста', 'Раз вы уже вышли к этому окну то, пожалуйста поставьте нам пятёрки')

def pas(): #2.0
    mb.showinfo('Как?', "Как вы нашли эту кнопку?")
    mb.showinfo('Как?', "Она же хорошо спрятана")
    ans = mb.askyesno('Как?', "Я надеюсь вы её случайно нашли")
    if ans == True:
        mb.showinfo('Как?', "Вам крупно повезло")
    elif ans == False:
        mb.showinfo('Терпение', "Штош раз у вас много лишнего времени")
        mb.showinfo('Наказание', 'Если вам нравится много кликать мышью то вот пожалуйста милости прошу')
        mb.showinfo('Наказание', "Я не дам так просто её закрыть пока ты не прожмёшь все кнопки Муа-ха-ха-ха-ха")

        for i in range(0, 1001):
            mb.showinfo('Зачем?', "Зачем?                        тык-клац-клац")
        for i in range(0, 40):
            mb.showinfo('', 'Аккуратнее                Осталось 40 кликов ты же не хочешь это пропустить?')
        mb.showinfo('', 'координаты следущей кнопки : x = 640, y =  404')

def joke():
    count = 0
    mb.showinfo('Хахаха', "Это вирус, мы вас обыграли");
    mb.showinfo("Учись", "И впредь не скачивай всё подряд")

    mb.askyesnocancel('Слышь', 'Чё самый(ая) умный(ая) что ли нашёл(ла) это?')
    mb.showinfo('', 'Подумай ещё раз')

    for i in range(0, 41):
        ans = mb.askyesnocancel('Слышь', 'Чё самый(ая) умный(ая) что ли нашёл(ла) это?')
        if ans == False: count+=1;
    mb.showinfo('', 'Будь терпелив(а)')
    for i in range(0, 11): mb.showinfo('', '                                            Отвечай внимательнее')
    for i in range(0, 51):
        ans = mb.askyesnocancel('Слышь', 'Ты глупый(ая)')
        if ans == True: count+=1;

    if count == 90:
        mb.showinfo("", "Хорошо я рад, что ты это признаёшь")
        mb.showinfo('', 'Молодец, на самом деле это не вирус я пошутил')
    else:
        delay(120);
        mb.showinfo('', 'Ты серьёзно, дождался(ась)?')
        mb.showinfo('', 'Молодец, на самом деле это не вирус я пошутил')


window = Tk()
window.geometry('470x300');
window["bg"] = 'white'

ent = Entry(window, width = 53, bd = 2, bg = "ghost white"); #1.2
combo = cb(window,  width = 50);
lbl1 = Label(window, text = "Введи Фамилию без ошибок ", font = (0, 20), fg = 'blue', bg = "white") #1.2
lbl2 = Label(window, text = "Или выбери", font = (0, 20), fg = 'blue', bg = "white" ) #1.2
btn = Button(window, text = 'Найти', height = 2, width = 40, bg = 'blue', fg = 'white', command = clicked)
lble = Label(window, text = "", bg = "white") #1.2
lblt = Label(window, text = "", bg = "white") #1.2
lbl3 = Label(window, text = '', font = (0, 20), fg = 'blue', bg = "white") #1.2
lbl4 = Label(window, text = "", font = (0, 20), fg = 'blue', bg = "white") #1.2
cbtn = Button(window, text = 'Копировать', height = 2, width = 10, bg = 'blue', fg = 'white', command = copy)
cbtn2 = Button(window, text = 'Копировать', height = 2, width = 10, bg = 'blue', fg = 'white', command = copy2)
lblp = Label(window, text = "8a Глеб", font = (0, 3), fg = 'gray', bg = "white") #1.2
btnp = Button(window, text = "", bg = "white", fg = "white", width = 1, bd = 0, command = name)
lbln = Label(window, text = '1.2', font = (0, 10), fg = 'blue', bg = "white") #1.2
btnpas = Button(window, text = "", bg = "red", fg = "white", width = 1, bd = 0, command = pas)
btnj = Button(window, text = "", bg = "red", fg = "white", width = 1, bd = 0, command = joke)


combo['value'] = Id.keys();
combo.current(1)

lbl1.grid(column = 0, row = 0); lbln.place(x = 400, y = 10)
ent.grid(column = 0, row = 1);
lbl2.grid(column = 0, row = 2);
combo.grid(column = 0, row = 3);
lble.grid(column = 0, row = 4); #для разделения комбобокса и кнопки
btn.grid(column = 0, row = 5);
ent.focus();
lbl3.grid(column = 0, row = 6); cbtn.grid(column = 1, row = 6);
lbl4.grid(column = 0, row = 8); cbtn2.grid(column = 1, row = 8);
lblt.place(x = 452, y = 160)
lblp.grid(column = 10, row = 13)
btnp.place(x = 480, y = 0)
btnpas.place(x = 105, y = 240)
btnj.place(x = 640, y =  404)


window.title('ID');
window.mainloop()
