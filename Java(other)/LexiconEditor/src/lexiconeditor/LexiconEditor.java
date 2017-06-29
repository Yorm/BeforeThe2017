package lexiconeditor;
// тут мне помогает joji - thom
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import static java.lang.System.exit;
import java.util.ArrayList;
import java.util.List;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Pos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Pagination;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


public class LexiconEditor extends Application {
    //
    BufferedReader answerReader;
    List answerList=new ArrayList<String>(); 
    //
    VBox[] mass; // в хэш мап го
    //
    int i=0;
    //
    public static void main(String[] args) {
        launch(args);
    }  //complite
    @Override
    public void start(Stage primaryStage) throws Exception {
        startBatFile();
        init(primaryStage);
        primaryStage.show();
    }//complite
    private void init(Stage primaryStage) { 
        Group root = new Group();
        primaryStage.setScene(new Scene(root, 260, 350));
        primaryStage.setTitle("Lexicon Editor");
        primaryStage.setResizable(false);
        
        GridPane gridAlert = new GridPane();
               gridAlert.setHgap(10);
               gridAlert.setVgap(10);  
               
        
        Pagination pagination = new Pagination();
        setControls(pagination);
        
        VBox controls = new VBox();
        controls.setAlignment(Pos.CENTER);
            Button record = new Button("Record to file");
            Button wCouter = new Button("WordCouter");
               
        pageFactory(pagination); 
        
        record.setOnAction((ActionEvent event) -> {
            for(int k=0;k<i;k++)
                for(int j=0;j<15;j++){
                    if(((CheckBox)(mass[k].getChildren().get(j))).isSelected()){
                        recordToIgnore(((CheckBox)(mass[k].getChildren().get(j))).getText());
                        removeFromAnswer(((CheckBox)(mass[k].getChildren().get(j))).getText());
                        ((CheckBox)(mass[k].getChildren().get(j))).setSelected(false);
                        ((CheckBox)(mass[k].getChildren().get(j))).setDisable(true);
                    }
                }
        });
        
        wCouter.setOnAction((ActionEvent event) -> {
            resetAll(pagination);
        });
        
        controls.getChildren().addAll(pagination,record,wCouter);
        gridAlert.add(controls, 0, 1);
        root.getChildren().add(gridAlert);
    }

////////////////////////////////////////////////////////////////////////////////     
    void recordToIgnore(String s){
        try{
            FileWriter ignoreWriter = new FileWriter("C:\\Users\\walte\\Desktop\\LexiconEditor\\ignore.txt",true);
            ignoreWriter.write(s + "\n");
            ignoreWriter.close();
        }catch(Exception e){
            System.out.print(e.getMessage());
        }  
    }//complite
    void removeFromAnswer(String s){
        try {
            FileWriter answerWriter = new FileWriter("C:\\Users\\walte\\Desktop\\LexiconEditor\\answer.txt");
            
            try {
                 for(int i =0;i<answerList.size(); i++){
                    if(answerList.get(i).toString().equals(s)){
                        answerList.remove(s); 
                        System.out.println(s);
                        i--;
                    }
                }
                
                for(Object o: answerList){
                    if(!o.toString().equals("-"))
                        answerWriter.write(o.toString()+'\n');
                }
                answerWriter.flush();
            } catch (Exception ex) {
                System.err.println("File answer.txt was not read correctly/cannot be created");
                System.exit(0);
            }
            
        } catch (IOException ex) {
            System.err.println("File answer.txt cannot be created");
            exit(0);
        } 
        
    }//complite
    void pageFactory( Pagination pag){
        pag.setPageFactory((Integer pageIndex) -> mass[pageIndex]); 
    }//complite
    void resetAll(Pagination p){
        answerList.clear();
        i=0;
        setControls(p);
        pageFactory(p); 
        startBatFile();
    }//complite   
    void startBatFile(){
        try {
            Runtime.getRuntime().exec("cmd /c startWC.bat");
        } catch (IOException ex) {
            System.err.println("startWC.bat error");
        } 
    }
    void setControls(Pagination p){       
        String line = null;
        try {
            answerReader = new BufferedReader(new FileReader("C:\\Users\\walte\\Desktop\\LexiconEditor\\answer.txt"));
        } catch (IOException ex) {
            System.err.println("File answer.txt was not found");
            exit(0);
        }
        try {
            while((line = answerReader.readLine())!=null){
                answerList.add(line);
                i++;
            }
            answerReader.close();
        } catch (Exception ex) {
            System.err.println("File resource.txt was not read correctly");
            System.exit(0);
        }
        
        for(int j=0;j<15-(i-(i/15*15));j++){
            answerList.add("-");
        }

        i=(int) (Math.round(i/15+0.5));
        mass = new VBox[i];
        System.out.println(i);
        for(int j=0;j<i;j++){
            VBox cell=new VBox();
            //cell.setAlignment(Pos.BASELINE_LEFT);
            for(int k=j*15;k<j*15+15;k++){
                CheckBox newCB= new CheckBox(answerList.get(k).toString());
                if(answerList.get(k).toString().equals("-"))
                    newCB.setDisable(true);
                newCB.isSelected();
                cell.getChildren().add(newCB);
            }
            mass[j]=cell;
        }
        
        p.setPageCount(i);
    } //complite
////////////////////////////////////////////////////////////////////////////////    
}
