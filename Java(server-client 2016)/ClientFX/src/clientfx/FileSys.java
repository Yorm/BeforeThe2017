package clientfx;
//Доступ к файловой системе
import java.io.File;
//
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
//
//============================================================================//
public class FileSys  {
    
    String path;
    VBox files ;
    VBox VBfls;
    Label pathLabel;
    Stage primaryStage;
    
    Label choice;
    
    boolean mode;
    
    FileSys(boolean m,Label c){
        mode = m;
        choice=c;
        path = "C:\\";
        files =new VBox();
        VBfls=new VBox();
        pathLabel = new Label(path);
        primaryStage = new Stage();
        if(mode)
            primaryStage.setTitle("Подберите себе файл");
        else
            primaryStage.setTitle("Подберите себе папку");
    }
    
    public void start() {        
        Group viev = new Group();              
        VBfls.getChildren().addAll(getB(path));  
        HBox controlB = new HBox(10);
            Button b_back=new Button("Назад");
                b_back.setStyle("-fx-base: orange;");
            Button chDir=new Button("Выбрать");
                chDir.setStyle("-fx-base: rgb(153,204,255)");

        chDir.setDisable(mode);//что то это так элегантно вышло что я аш удивился
        chDir.setOnAction(event->{
            choice.setText(path);
            primaryStage.close();
        });

        b_back.setOnAction(event->{
            path=new File(path).getParent();
            files.getChildren().remove(VBfls);
            VBfls=getB(path);
            files.getChildren().add(VBfls);  
        });
        controlB.getChildren().addAll(b_back,chDir);   
        files.getChildren().addAll(controlB,VBfls);                    
        viev.getChildren().add(files);
        
        Scene scene = new Scene(viev, 400, 600);
        
        primaryStage.setScene(scene);
        primaryStage.show();
    }

void buttonDirectory(Button d){
    d.setStyle("-fx-base: rgb(255,255,102)");
    d.setOnAction(new EventHandler<ActionEvent>() {          
            @Override
            public void handle(ActionEvent event) {
                path = path.concat(d.getText().concat("\\"));
                files.getChildren().remove(VBfls);
                VBfls=getB(path);
                files.getChildren().add(VBfls);  
        }
    }); 
}
void buttonFile(Button f){
    f.setStyle("-fx-base: rgb(153,204,255)");
    f.setOnAction(new EventHandler<ActionEvent>() {          
        @Override
        public void handle(ActionEvent event) {
            choice.setText(path+f.getText());
            primaryStage.close();
        }
    }); 
}
    public VBox getB(String pathS){
        //System.out.println(pathS);
        VBox elements=new VBox();
        elements.getChildren().addAll(new Label(pathS)); 
        File dir = new File(pathS);

        if(dir.listFiles()!=null){  
            File[] unit = dir.listFiles();
            {
                for(int i=0; i<unit.length; i++)           
                {
                    
                    if(unit[i].isDirectory()&&!unit[i].getName().equals("YouServerFolder")){
                        Button newB=new Button(unit[i].getName());
                        buttonDirectory(newB);
                        elements.getChildren().add(newB); 
                    }     
                }
                if(mode)
                    for(int i=0; i<unit.length; i++)           
                    {
                        if (unit[i].isFile()){
                            Button newB=new Button(unit[i].getName());
                            buttonFile(newB);
                            elements.getChildren().add(newB); 
                        }
                    }
            }
        }else {
            files.getChildren().remove(VBfls);
        }
        return elements;     
    }
    
}
