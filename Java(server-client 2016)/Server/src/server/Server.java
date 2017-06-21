package server;

import java.net.*;
import java.io.*;
import java.util.LinkedList;

public class Server implements Runnable{
    final String path= "C://YouServerFolder//";
    int port;
    ServerSocket ss;
    ConnectedClient newClient;

    public Server(){
        try
        {
            port = 6666;//6989
            new File(path).mkdir();
            ss= new ServerSocket(port);
            newClient = new ConnectedClient();
            System.out.println("+-------------------------------------------+");  
            System.out.println("              Сервер запущен                 ");
            System.out.println("+-------------------------------------------+");  
        }
        catch(Exception e){System.err.println("//sevrer crashed");}       
    }

    public static void main(String[] arg)    {
        new Thread(new Server()).start();     
    }

    public void run(){
        try
        {
        while(true)
        {       
            newClient.newConnection(ss.accept());
            System.out.println("Новый клиент подключился");
        }
        }catch(Exception e){System.err.println("//client problem");}
    }
    
    
    class ConnectedClient{
        
        LinkedList<ServiceClient> clients;

        ConnectedClient() {
            clients = new LinkedList<ServiceClient>();
        }
            
        void newConnection(Socket soc){
            new Thread(new ServiceClient(soc)).start();
        }
        void addServiceClient(ServiceClient newClient){
            System.out.println("Клиент записан в лист");   
            clients.add(newClient);
            for(ServiceClient sc:clients)
                if(sc!=newClient)
                    sc.sendName(newClient.clientName);

            for(ServiceClient sc:clients){
                newClient.sendName(sc.clientName);
            }
            
            File dir = new File(path);
            if(dir.listFiles()!=null){  
                File[] unit = dir.listFiles();
                    for(int i=0; i<unit.length; i++)           
                    {
                        if (unit[i].isFile())
                            newClient.sendFileName(unit[i].getName());
                    }
            }
            
            
            System.out.println("+-------------------------------------------+");  
        }
        
        void addAvailableFile(ServiceClient client,String filename){
            System.out.println("Рассылаются кнопки");  
            for(ServiceClient sc:clients)
                if(sc!=client)
                    sc.sendFileName(filename);
                else if(sc==client)
                    client.sendFileName(filename);
            System.out.println("+-------------------------------------------+");  
        }
        void delServiceClient(ServiceClient delClient){
            for(ServiceClient sc:clients)
                if(sc!=delClient)
                    sc.delName(delClient.clientName);
            clients.remove(delClient);
            
        }
        
        class ServiceClient implements Runnable{
                String clientName;
                Socket socket;
                InputStream sin;
                OutputStream sout;
                
                ServiceClient(Socket soc){
                    try
                    {
                    socket = soc;
                    sin = socket.getInputStream();
                    sout = socket.getOutputStream();
                    System.out.println("Клиент обслуживается");
                    }catch(Exception e){System.err.println("//ServiceClient constructor error");}
                }
                
                @Override
                public void run(){
                    try
                    {
                    while(true)
                    {
                        //Принимаем заголовок
                        byte[] Hbuffer = new byte[4];
                        sin.read(Hbuffer);
                        String header = new String(Hbuffer,"UTF-8").trim();  
                        //Што делать
                        switch(header)
                        {
                            case "senN":
                            {
                                receiveName(); 
                            }break;
                            case "recF":
                            {
                                sendFile(); 
                            }break;
                            case "senF":
                            {
                                receiveFile();
                            }break;
                            // default: System.out.println("BE DA");
                        } 
                    }
                    }catch(Exception e){
                        System.err.println("//HEADER ERROR");
                         delServiceClient(this);
                    }
                }
                
                void receiveName(){
                    try 
                    {
                        System.out.println("+-------------------------------------------+");  
                        byte[] Nbuffer = new byte[16];
                        sin.read(Nbuffer);
                        clientName = new String(Nbuffer,"UTF-8").trim();
                        System.out.println("Приняли имя нового клиента: "+clientName);
                        addServiceClient(this);
                    }catch(Exception e){System.err.println("//name client error");}
                }
                
                
                void receiveFile (){          
                    try 
                    {
                        System.out.println("+-------------------------------------------+"); 
                        System.out.println("Сервер принимает файл");  
                        //Принимаем имя
                        byte[] Nbuffer = new byte[255];
                        sin.read(Nbuffer);
                        String fileName = new String(Nbuffer,"UTF-8").trim();
                        System.out.println("Имя файла:"+fileName);
                        //Буферы для файла
                        byte[] buffer = new byte[65536];
                        FileOutputStream f_out = new FileOutputStream("C://YouServerFolder//"+fileName);
                        BufferedInputStream b_is = new BufferedInputStream(socket.getInputStream());              
                        //Принимаем размер
                        long sf;    
                        DataInputStream d_is = new DataInputStream(socket.getInputStream());
                        sf=d_is.readLong();
                        System.out.println("Размер файла:"+sf);
                        //Принимаем файл
                        while (sf > 0) {
                            int i = b_is.read(buffer);
                            f_out.write(buffer, 0, i);
                            sf-= i;
                        }
                        f_out.close();
                        System.out.println("Файл получен");
                        
                        addAvailableFile(this,fileName);
                    } catch(Exception x) { x.printStackTrace(); }
                }
                
                void sendFile() throws IOException{
                    System.out.println("+-------------------------------------------+");  
                    System.out.println("Сервер начинает отправлять файл");  
                    byte[] Hbuffer=new byte[4];
                    Hbuffer="senF".getBytes();
                    sout.write(Hbuffer); 

                    byte[] Nbuffer = new byte[255];
                    sin.read(Nbuffer);
                    String fileName = new String(Nbuffer,"UTF-8").trim();
                    System.out.println("Файл "+fileName+" подключен");
                        
                    try
                    {   
                        sout.write(Nbuffer);       
                        System.out.println("Имя файла отправлено");   
                    }
                    catch (Exception x) {System.err.println("//fileName error");}

                    try 
                    {
                        byte[] buffer = new byte[65536];//8192 64
                        File f = new File("C://YouServerFolder//"+fileName);      
                        FileInputStream f_is = new FileInputStream(f);
                        BufferedOutputStream b_os = new BufferedOutputStream(socket.getOutputStream());                
                        long sf=f.length();
                        //Отправляю размер
                        try 
                        {  
                            DataOutputStream d_os= new DataOutputStream(socket.getOutputStream());
                            d_os.writeLong(sf);
                            System.out.println("Размер файла отправлен:"+sf);
                        } 
                        catch (Exception x) { System.err.println("//fileSize error"); }
                        //Данные отправляю
                        while (sf > 0) {
                            int i = f_is.read(buffer);
                            b_os.write(buffer, 0, i);
                            sf-= i;
                        }
                        b_os.flush();
                        f_is.close();
                        System.out.println("Файл отправлен");
                        System.out.println("+-------------------------------------------+");  
                    }catch (FileNotFoundException ex){}
                }
                
                void sendName(String n){
                    try 
                    {  
                        byte[] Hbuffer=new byte[4];
                        Hbuffer="senN".getBytes();
                        sout.write(Hbuffer); 
                        DataOutputStream d_os= new DataOutputStream(socket.getOutputStream());
                        d_os.writeUTF(n); 
                        System.out.println("Имя клиента отправлено");   

                    }catch (Exception x){System.err.println("//sendName error");}
                }
                
                void delName(String n){
                    try 
                    {  
                        byte[] Hbuffer=new byte[4];
                        Hbuffer="delN".getBytes();
                        sout.write(Hbuffer); 
                        DataOutputStream d_os= new DataOutputStream(socket.getOutputStream());
                        d_os.writeUTF(n); 
                        System.out.println("Имя клиента удалено");   

                    }catch (Exception x){System.err.println("//delName error");}
                }
               void sendFileName(String n){
                   try 
                    {  
                        byte[] Hbuffer=new byte[4];
                        Hbuffer="snFN".getBytes();
                        sout.write(Hbuffer); 
                        DataOutputStream d_os= new DataOutputStream(socket.getOutputStream());
                        d_os.writeUTF(n);
                        System.out.println("Имя кнопки отправлено");
                    }catch (Exception x){System.err.println("//sendFileName error");}
               }

                
        }
        
    }
    
}