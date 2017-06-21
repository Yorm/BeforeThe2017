package wordcounter;
////////////////////////////////////////////////////////////////////////////////
//предложеньце у меня, в блоке catch если что то выводим - давай писать вместо out - err, потому что я с твоим
//"File ignore.txt was found" в первый раз испугался
import java.io.*;
//
import static java.lang.System.exit;
//
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//
public class WordCounter{
//
    BufferedReader resourceReader;
//   
    FileWriter answerWriter;
    List answerList;
//   
    BufferedReader ignoreReader;
    FileWriter ignoreWriter;
    Boolean ignore;
    List ignoreList;
//
    public WordCounter(){
        ignore = true;
        try {
            resourceReader = new BufferedReader(new FileReader("resource.txt")); 
        } catch (FileNotFoundException ex) {
            System.err.println("File resource.txt was not found");
            exit(0);
        }
        try {
            answerWriter = new FileWriter("answer.txt");
        } catch (IOException ex) {
            System.err.println("File answer.txt cannot be created");
            exit(0);
        }

        try {
            ignoreReader = new BufferedReader(new FileReader("ignore.txt"));
            ignoreList = new ArrayList<String>();
            System.out.println("File ignore.txt was found");
        } catch (FileNotFoundException ex) {
            System.err.println("File ignore.txt was not found");
            ignore = false;
        }
    }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    /*
    I love you, you fool!
    You want to destroy it in a moment?
    You want me to was eaten the whores?
    They are outside - 
    Selling cars full of my unwithdrawn movies and my unwritten books
    */
    public static void main(String[] args) {
        WordCounter session = new WordCounter();
        session.readResource();
        
        if(session.ignore){    
            session.readIgnore();
            session.filter();
        }
        session.sort();
        session.writeAnswer();
        System.out.println("Success");
        
    }
//.....................//    
    void readResource(){//Бьем ресурс на отдельные слова, не разобрался до конца с if-else
        Map<String,Integer> wordsToAnswer = new HashMap<String, Integer>();
        
        String line = null;
        String[] words = null;
        
        try {
            while((line = resourceReader.readLine())!=null){
                line = line.replaceAll("\\,|\\:|\\.|\\!|\\'s|\\?|\\-|\\/|\\[|\\]|\\\"|\\_|\\'|\\;", "");
                words = line.split("\\s", -1);
                System.out.println(line +" линия - слова "+Arrays.asList(words));
                for(int i = 0; i<words.length;i++){
                    words[i]=words[i].toLowerCase();
                    if(!textOrNumber(words[i])){//не очень красиво?
                        if(wordsToAnswer.containsKey(words[i]))
                            wordsToAnswer.replace(words[i], wordsToAnswer.get(words[i])+1);
                        else{               
                            wordsToAnswer.put(words[i], 1);
                        }
                    }//да
                }
            }
            answerList = new ArrayList(wordsToAnswer.entrySet());
        } catch (Exception ex) {
            System.err.println("File resource.txt was not read correctly");
            System.exit(0);
        }
    }
//.....................//    
    void readIgnore(){//Очищаем, сортируем, добавляем, обновляем
        String line = null;
        String[] words = null;
        
        try{
            while((line = ignoreReader.readLine())!=null){
                line = line.replaceAll("\\,|\\:|\\.|\\!|\\'s|\\?|\\-|\\/|\\[|\\]|\\\"|\\_|\\'|\\;", "");
                words = line.split("\\s", -1);
                for(int i = 0; i<words.length;i++){
                    words[i]=words[i].toLowerCase();
                    
                    if( !textOrNumber(words[i]) ){
                        ignoreList.add(words[i]);
                    }                 
                }
            }
        } catch (Exception ex) {
            System.err.println("File ignore.txt was not read correctly");
            System.exit(0);
        }
       
       Set ignoreWords = new TreeSet(ignoreList);
       ignoreList.clear();
       
       ignoreList.addAll(new ArrayList( ignoreWords));
       
       updateIgnoreList();
    }//complite
//.....................//   
    boolean textOrNumber(String s){
        try{Integer.parseInt(s);}
        catch(Exception ex){return false;}
        return true;
    }//complite
//.....................//   
    void updateIgnoreList(){
        try {
            ignoreWriter = new FileWriter("ignore.txt");
        } catch (IOException ex) {
            System.err.println("File ignore.txt cannot be created");
            exit(0);
        } 
        try{
            for(Object o: ignoreList){
                ignoreWriter.write(o.toString()+'\n');
            }
            ignoreWriter.flush();
        } catch (Exception ex) {
            System.err.println("File ignore.txt was not completely written");
            System.exit(0);
        }
    }//complite
//.....................// 
    void filter(){//Удаляем из ресурсов игнор-слова
        for(int i =0;i<answerList.size(); i++){
            Map.Entry<String, Integer> unit = (Map.Entry<String, Integer>)answerList.get(i);  
            if(ignoreList.contains(unit.getKey())){
                answerList.remove(unit);
                i--;
            }
        }
    }//complite
//.....................// 
    void sort(){// сортируем и ничего не надо писать
        Collections.sort(answerList, (Map.Entry<String, Integer> a, Map.Entry<String, Integer> b)->b.getValue() - a.getValue());
    }//complite
//.....................// 
    void writeAnswer(){
        Map.Entry<String, Integer> unit;
        try {
            for(Object o: answerList){
                unit = (Map.Entry<String, Integer>)o;
                answerWriter.write(unit.getKey()+" - "+unit.getValue()+'\n');
            }
            answerWriter.flush();
        } catch (Exception ex) {
            System.err.println("File answer.txt was not completely written");
            System.exit(0);
        }
        
    }//complite
//.....................// 
}
