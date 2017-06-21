package clientfx;
//Клиент
import java.net.*;
import java.io.*;
import java.util.Optional;
//

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;

import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

//============================================================================//
public class ClientFX extends Application {  
//----------------------------------------------------------------------------//  
    File fileFromSend;
    OutputStream sout;
    int serverPort; 
    
    String address;
    String clientName;
    
    InetAddress ipAddress; 
    Socket socket; 
    
    
    
    VBox onlineUsers = new VBox();
    VBox addedFiles = new VBox();
    Label lDirectory;
//----------------------------------------------------------------------------//
    @Override
    public void start(Stage primaryStage) {
        splash();
        connection();
        //primaryStage.setResizable(false);
        
        primaryStage.setTitle("Клиент "+clientName);
        
        Group viev = new Group();
        BorderPane root = new BorderPane();
        
        HBox form = new HBox(20);
            VBox controls = new VBox();
                Button wimFile = new Button("Выбрать файл ");
                Label lFile= new Label("\\file\\");
                Button send = new Button("    Отправить   ");
                Button wimDirectory = new Button("Выбрать папку");
                    lDirectory= new Label("\\directory\\");
                    
        Label inList= new Label("Клиенты online");
        Label headFiles= new Label("Доступные файлы");

        controls.getChildren().addAll(lDirectory,wimDirectory,wimFile,lFile,send);//ipField,clientName,connect,
        onlineUsers.getChildren().addAll(inList);
        addedFiles.getChildren().addAll(headFiles);
        
        form.getChildren().addAll(controls,addedFiles,onlineUsers);
        root.setCenter(form);         
        viev.getChildren().add( root);
        
        
        //выбор файла
        wimFile.setOnAction(new EventHandler<ActionEvent>() {          
            @Override
            public void handle(ActionEvent event) {
                new FileSys(true,lFile).start();
            }
        });
        lFile.textProperty().addListener(event->{
            fileFromSend=new File(lFile.getText());
        });
        //выбор папки
        wimDirectory.setOnAction(new EventHandler<ActionEvent>() {          
            @Override
            public void handle(ActionEvent event) {
                new FileSys(false,lDirectory).start();    
            }
        });
        //отправка файла
        send.setOnAction(new EventHandler<ActionEvent>() {          
            @Override
            public void handle(ActionEvent event) {
                if(!lFile.getText().equals("\\file\\")){
                    System.out.println("+-------------------------------------------+"); 
                    System.out.println("Отправка файла");
                    Thread T = new Thread(new SendFile(fileFromSend,socket));//может поменяешь подход, объеденишь этот класс с главным?
                    T.start();
                }else{
                    Alert noDownload = new Alert(Alert.AlertType.ERROR);
                    noDownload.setTitle("Ошибка отправки");
                    noDownload.setHeaderText(null);
                    noDownload.setContentText("Не выбран файл для отправки");
                    noDownload.showAndWait();
                }
            }
        });
   
        Scene scene = new Scene(viev, 350, 200);
        
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    public final void splash(){
        ////////////////////////////////////////////////////
        Alert setTable = new Alert(Alert.AlertType.NONE);
            setTable.setTitle("Подключение");
            setTable.setHeaderText("Введите Адрес и Имя в сети");     
            setTable.setGraphic(new ImageView(this.getClass().getResource("cat.png").toString()));
        
            TextField ipField = new TextField("127.0.0.1");
                    ipField.setPromptText("IP адресс");
                    ipField.setMaxWidth(98);
            TextField clientNameTF = new TextField();
                    clientNameTF.setPromptText("Имя");
                    clientNameTF.setMaxWidth(98);
        
            GridPane gridAlert = new GridPane();
                    gridAlert.setHgap(10);
                    gridAlert.setVgap(10);  
                    gridAlert.add(ipField, 0, 0);
                    gridAlert.add(clientNameTF, 0, 1);
            
        setTable.getDialogPane().setContent(gridAlert);
          
        ButtonType btnOK = new ButtonType("Ок");
        ButtonType btnCancel = new ButtonType("Выход");
        setTable.getButtonTypes().setAll(btnCancel,btnOK);
        Node btnok = setTable.getDialogPane().lookupButton(btnOK);
            btnok.setDisable(true);
             
        clientNameTF.textProperty().addListener(event ->{
            btnok.setDisable(false);
            if(clientNameTF.getText().length()>=17){
                String str=clientNameTF.getText();
                str = str.length()>=17 ? str.substring(0,16): str;
                clientNameTF.setText(str);
            }
        });
        
        Optional<ButtonType> result = setTable.showAndWait();
            if (result.get() == btnCancel){   
                System.exit(1);
        }   
        address=ipField.getText();
        clientName=clientNameTF.getText();

    }
    
    public void connection(){
        serverPort=6666;
        try
        {
            ipAddress = InetAddress.getByName(address); 
            socket = new Socket(ipAddress, serverPort); 
            sout = socket.getOutputStream();

            try //отправляем заголовок нашего сообщения
            {
                byte[] Hbuffer=new byte[4];
                Hbuffer="senN".getBytes();
                sout.write(Hbuffer); 
            }
            catch (Exception x) { System.err.println("//senN header error"); }
            try //отправляем имя клиента
            {
                byte[] Hbuffer=new byte[16];
                Hbuffer=clientName.getBytes();
                sout.write(Hbuffer); 
            }
            catch (Exception x) { System.err.println("//client name sending error"); }

            //создаем слушателя сервера
            Thread T = new Thread(new OnlineScreen(socket));
            T.setDaemon(true);
            T.start();                  
        }
        catch (Exception x) {
            Alert noConnect = new Alert(Alert.AlertType.ERROR);
            noConnect.setTitle("Ошибка подключения");
            noConnect.setHeaderText(null);
            noConnect.setContentText("Неверно введен IP адрес / сервер отключен");
            noConnect.showAndWait();
            System.exit(1);
            System.err.println("//connect error"); x.printStackTrace();
        } 
    }

//----------------------------------------------------------------------------//  
    public static void main(String[] args) {
        launch(args);
    }
//----------------------------------------------------------------------------//  
    void addName(String s){
        Platform.runLater(new Runnable(){
            public void run()
            {
                onlineUsers.getChildren().add(new Label(s));
            }
        });
    }
    void delName(String s){
        Platform.runLater(new Runnable(){
            public void run()
            {

                Object[] lbl = onlineUsers.getChildren().toArray();
                Label l = new Label(s);
                for(Object onlU:lbl){
                    if(((Label)onlU).getText().equals(l.getText())){
                        onlineUsers.getChildren().remove(onlU);
                        System.out.println(Thread.currentThread().getName());
                        break;
                    }
                }

                System.out.println(s);
            }
        });
    }
//----------------------------------------------------------------------------//  
    void addFName(String s){
        Platform.runLater(new Runnable(){
            public void run()
            {
                try
                {   
                Button newB = new Button(s);
                newB.setMaxWidth(100);
                newB.setOnAction(new EventHandler<ActionEvent>() {          
                    @Override
                    public void handle(ActionEvent event) {
                        if(!lDirectory.getText().equals("\\directory\\"))
                            try //отправляем заголовок нашего сообщения
                            {
                                System.out.println("Скачиваю файл в "+lDirectory.getText());
                                byte[] Hbuffer=new byte[4];
                                Hbuffer="recF".getBytes();
                                sout.write(Hbuffer); 

                                byte[] Nbuffer=new byte[s.length()];
                                Nbuffer=s.getBytes();
                                sout.write(Nbuffer);       
                                System.out.println("Имя файла с кнопки отправлено");   

                            }catch (Exception x) { System.err.println("//recF header error"); x.printStackTrace();}
                        else {
                            Alert noDownload = new Alert(Alert.AlertType.ERROR);
                            noDownload.setTitle("Ошибка загрузки");
                            noDownload.setHeaderText(null);
                            noDownload.setContentText("Не указана папка загрузки");
                            noDownload.showAndWait();
                        }

                    }
                });
                addedFiles.getChildren().add(newB);
                }catch(Exception e){System.err.println("//error newB");}
            }
        });
    }
//----------------------------------------------------------------------------//    
    class OnlineScreen implements Runnable{
//----------------------------------------------------------------------------// 
        InputStream sin;
        OutputStream sout;   
        Socket socket;
//----------------------------------------------------------------------------// 
        public OnlineScreen(Socket soc ){
            try 
            {
                socket= soc;
                sin = socket.getInputStream();
                sout = socket.getOutputStream();
            }
            catch (Exception x) { System.err.println("//OnlineScreen constructor error"); x.printStackTrace();}
        }
//----------------------------------------------------------------------------//      
        public void run(){  
            try 
            {
            while(true){
                byte[] Hbuffer = new byte[4];
                sin.read(Hbuffer);
                switch(new String(Hbuffer,"UTF-8").trim()){
                    
                    case "senN":{
                        DataInputStream d_is= new DataInputStream(socket.getInputStream());
                        String clientName= d_is.readUTF();
                        System.out.println("Сервер вернул имя клиента: "+clientName  );
                        addName(clientName);
                    } break;
                    
                    case "delN":{
                        DataInputStream d_is= new DataInputStream(socket.getInputStream());
                        String clientName= d_is.readUTF();
                        System.out.println("Сервер удаляет имя клиента: "+clientName  );
                        delName(clientName);
                    } break;
                    
                    case "snFN":{
                        DataInputStream d_is= new DataInputStream(socket.getInputStream());
                        String fileName= d_is.readUTF();
                        addFName(fileName);
                        System.out.println("Сервер вернул имя файла: "+fileName  );
                        System.out.println("+-------------------------------------------+");  
                    } break;
                    
                    case "senF":{
                        System.out.println("+-------------------------------------------+");  
                        System.out.println("Принимаем файл");  
                        String path =  lDirectory.getText();
                        //Принимаем имя
                        byte[] Nbuffer = new byte[255];
                        sin.read(Nbuffer);
                        String fileName = new String(Nbuffer,"UTF-8").trim();
                        System.out.println("Имя файла "+fileName);
                        //Буферы для файла
                        byte[] buffer = new byte[65536];
                        System.out.println("Путь "+path+fileName);
                        FileOutputStream f_out = new FileOutputStream(path+fileName);
                        BufferedInputStream b_is = new BufferedInputStream(socket.getInputStream());              
                        //Принимаем размер
                        long sf;    
                        DataInputStream d_is = new DataInputStream(socket.getInputStream());
                        sf=d_is.readLong();
                        System.out.println("Размер файла: "+sf);
                        //Принимаем файл
                        while (sf > 0) {
                            int i = b_is.read(buffer);
                            f_out.write(buffer, 0, i);
                            sf-= i;
                        }
                        f_out.close();
                        //b_is.close();
                        System.out.println("Файл успешно принят");
                        System.out.println("+-------------------------------------------+");            
                    } break;
                }
            }    
            }
            catch (Exception x) { System.err.println("//HEADER ERROR");}                  
        }
        
        void addOnl(){
            
        }
        void delOnl(){
            
        }
    }
//----------------------------------------------------------------------------//  
}

//============================================================================//  
class SendFile implements Runnable{
//----------------------------------------------------------------------------//  

    Socket socket; 
    
    InputStream sin;
    OutputStream sout;
    
    String line;
    
    File fileFromSend;
//----------------------------------------------------------------------------//    
    public SendFile(File ffs,Socket s){//Конструктор
        fileFromSend = ffs;
        try
        {
            socket = s;
            sin = socket.getInputStream();
            sout = socket.getOutputStream();
        }
        catch (Exception x) {System.err.println("//SendFile constructor error");}
    }  
//----------------------------------------------------------------------------//  
    public void run(){
        try //отправляем заголовок
        {
            byte[] Hbuffer=new byte[4];
            Hbuffer="senF".getBytes();
            sout.write(Hbuffer);         
        }
        catch (Exception x) { System.err.println("//senF header error");}
        
        try 
        {     
            //Телепортирую имя
            sendName();                
            //Отправка файла
            sendFile();
            //
            System.out.println("Конец отправки");
            System.out.println("+-------------------------------------------+");  
        }
        catch (Exception x) { System.err.println("run"); x.printStackTrace();}
    }    
//----------------------------------------------------------------------------//   
    void sendName(){//Для отправки имени
        try
        {    
            line=fileFromSend.getName();
            byte[] Nbuffer=new byte[line.length()];
            Nbuffer=line.getBytes();
            sout.write(Nbuffer);       
            System.out.println("Имя файла "+line+" отправлено");   
        }
        catch (Exception x) {System.err.println("//sendFileName error");}
    }
//----------------------------------------------------------------------------//  
    void sendFSize(long fs){//Для отправки размера файла
        try 
        {  
            DataOutputStream d_os= new DataOutputStream(socket.getOutputStream());
            d_os.writeLong(fs);
            System.out.println("Размер файла "+fs+" отправлен");
        } 
        catch (Exception x) { System.err.println("//sendFSize error"); }
    } 
//----------------------------------------------------------------------------//  
    void sendFile(){//Для отправки файла
        try 
        {  
        try 
        {
            byte[] buffer = new byte[65536];//8192 64
            File f = fileFromSend;      
            FileInputStream f_is = new FileInputStream(f);
            BufferedOutputStream b_os = new BufferedOutputStream(socket.getOutputStream());                
            long sf=f.length();
            //Отправляю размер
            sendFSize(sf);
            //Данные отправляю
            while (sf > 0) {
                int i = f_is.read(buffer);
                b_os.write(buffer, 0, i);
                sf-= i;
            }
            b_os.flush();
            f_is.close();
            System.out.println("Файл отправлен");  
        }catch (FileNotFoundException ex){System.err.println("//File Not Found");}
        }catch (Exception x) {System.err.println("//sendFile error");}      
    }
//----------------------------------------------------------------------------//  
}
