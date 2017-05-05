from Tkinter import *
import re
import Tkinter
import xml.etree.ElementTree as ET
import itertools
import ttk
class simpleapp_tk(Tk):
    def __init__(self,parent):
        Tk.__init__(self,parent)
        self.parent = parent
        
        self.initialize()
	#self.LoadTable()
 
    def initialize(self):
        self.grid()
 
        frame = Frame(self, borderwidth=2, relief="sunken", width=1107, height=50)
        frame.grid(columnspan=3,row = 0)
 
        a = Label(frame,text = "Sensor_processing", fg = "red", font = 20)
        a.place(in_=frame, anchor="c", relx=.5, rely=.5)
        
        self.frame1 = Frame(self, borderwidth=2, relief="sunken", width = 1100, height=600)
        self.frame1.grid(column = 0,row = 1, sticky = "WN")
	self.frame11 = Frame(self, borderwidth=2, relief="sunken", width = 300, height=90)
        self.frame11.grid(column = 0,row = 1, sticky = "WN")
	
	self.t=Text(self.frame11, borderwidth=1,bg='white',relief="sunken",width=50,height=27)
	self.t.place(in_=self.frame11)
	self.f=Button(self.frame1,text="quit",fg="purple",font=15,command=quit)
	self.f.place(in_=self.frame1,anchor="center",relx=.6,rely=.9)
	self.button=Button(self.frame1,text="click_here_to_proceed",fg="purple",font=15,command=self.click_here_to_proceed)
	self.button.place(in_=self.frame1,anchor="center",relx=.2,rely=.9)

	#self.frame12 = Frame(self, borderwidth=2, relief="sunken", width = 100, height=60)
        #self.frame12.grid(column = 0,row = 1, sticky = "NE")
	#self.frame13= Frame(self, borderwidth=2, relief="sunken", width = 100, height=60)
	#self.frame13.grid(column = 0,row = 1, sticky = "NE")
  	#self.k.destroy()
	tree = ET.parse('config.xml')
	root = tree.getroot()
	#print root.tag
	i = 0
	xml_list = []
	for child in root:
		xml_list.append(child.tag)
		xml_list.append(root[i].text)
	#	print dict(child.tag)
		i = i+1
	dct = dict(itertools.izip_longest(*[iter(xml_list)] * 2, fillvalue=""))
	for i,v in dct.items():
	    k=i,v
	    print k
	    print '\n'
	    self.t.insert(END,k)
	    self.t.insert(END,'\n')
	    
	    #self.T = Text(self.t, height=2, width=23)
	    #self.T.pack()
	   # self.T.insert(END, k)
       	#self.button = Button(self.frame1, text="QUIT", fg="purple",command=quit)
        #self.button.place(in_=self.frame1,relx=.87,rely=.23)
	#self.results=Label(self.frame1,text ="")
	#self.results.place(in_=self.frame1,relx=.1,rely=.6)
	self.Results = Label(self.frame1, text =" ")
	self.Results.place(in_=self.frame1,relx=.35,rely=.6)
	#self.button = Button(self.frame1, text="click_here_to_proceed", fg="purple",command=self.click_here_to_proceed)
        #self.button.place(in_=self.frame1,relx=.45,rely=.8)
    def click_here_to_proceed(self):
	self.frame11.destroy()
	#self.Results.destroy()
	self.button.destroy()
	#self.f.destroy()
	self.button1 = Button(self.frame1, text="Click_to_see_the_output", fg="purple",command=self.CreateUI)
        self.button1.place(in_=self.frame1,relx=.47,rely=.23)
	#self.button2 = Button(self.frame1, text="QUIT", fg="purple",command=quit)
        #self.button2.place(in_=self.frame1,relx=.87,rely=.23)
    def CreateUI(self):
	self.button1.destroy()
	self.frame12 = Frame(self, borderwidth=2, relief="sunken", width =500, height=120)
        self.frame12.grid(column = 0,row = 1, sticky = "WN")
        tv = ttk.Treeview(self.frame12)
	tv.grid(column = 0,row = 1, sticky = "WN")
        tv['columns'] = ('Sensor', 'Attribute','Output')
        tv.heading("#0", text='Sensor_hubid', anchor='w')
        tv.column("#0", anchor="w")
        tv.heading('Sensor', text='Sensor')
        tv.column('Sensor', anchor='center', width=100)
        tv.heading('Attribute', text='Attribute')
        tv.column('Attribute', anchor='center', width=100)
        tv.heading('Output', text='Output')
        tv.column('Output', anchor='center', width=100)
        tv.grid(sticky = N)
        self.treeview = tv
        self.grid_rowconfigure(0, weight = 1)
        self.grid_columnconfigure(0, weight = 1)
	self.load=Button(self.frame1,text="Quit",fg="purple",command=quit)
	self.load.place(in_=self.frame1,relx=.34,rely=.23)
	#self.button = Button(self.frame1, text="QUIT", fg="purple")
        #self.button.place(in_=self.frame1,relx=.87,rely=.23)
	self.Load_data()
    def Load_data(self):
	tree = ET.parse('config.xml')
	root = tree.getroot()
	#print root.tag
	i = 0
	xml_list = []
	for child in root:
		xml_list.append(child.tag)
		xml_list.append(root[i].text)
	#	print dict(child.tag)
		i = i+1
	dct = dict(itertools.izip_longest(*[iter(xml_list)] * 2, fillvalue=""))
	string1=" "
	string3=" "
	string2=" "
	for i in dct.keys():
		value = dct[i]
		if(i == "SENSOR" ):
			string2 = str(value)
			#string1=string1 + '\t'
		elif ( i== "MAC"):
			string1=str(value)
		elif(i=="ATTRIBUTES"):
			string3=str(value)
		
	#print string1,string2,string3
	stdc=ctypes.CDLL("libc.so.6")  #library for c
	#jlib = ctypes.CDLL("/usr/include/json/");
        obj = ctypes.CDLL("/home/kathirah/final_project_code/poc_dm/lib_final.so")
        obj.main()
	   
        self.treeview.insert('', 'end', text=string1, values=(string2,string3))
	#self.treeview.insert('', 'end', text="First", values=('10:00','10:10', 'Ok'))
	
if __name__ == "__main__":
    sensor = simpleapp_tk(None)
    sensor.title('SENSOR')
    sensor.geometry("1107x650")
    sensor.mainloop()
 
