package com.company;

import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import java.awt.Color;

import static java.lang.Math.abs;

public class MainForm extends JFrame {
    private JPanel mainPanel;
    private JButton restartButton;
    private JLabel flagsLabel;
    private JLabel timerLabel;
    private JPanel innerPanel;
    private Font font = new Font("Arial", Font.BOLD, 12);
    private Color color = new Color(159, 159, 191);
    private JPanel[][] holders;
    private JButton[][] buttons;
    private JLabel[][] labels;
    private int[][] mineField;
    private int height = 16;
    private int width = 16;
    private int maxMins = 40;
    private int activeCells;
    private int flagsCount = maxMins;
    private int secondCount = 0;
    private Timer timer;
    private GameStatus gameStatus;
    private Color buttonColor;
    private Color labelColor;

    public MainForm() {
        gameStatus = GameStatus.BEFORE;

        setContentPane(mainPanel);

        setResizable(false);

        innerPanel.setLayout(new GridLayout(height, width));
        innerPanel.removeAll();
        innerPanel.setPreferredSize(new Dimension(width * 40, height * 40));
        pack();
        innerPanel.setSize(innerPanel.getPreferredSize());

        holders = new JPanel[width][height];
        buttons = new JButton[width][height];
        labels = new JLabel[width][height];
        mineField = new int[width][height];

        ButtonFlagger buttonFlagger = new ButtonFlagger();
        ButtonOpener buttonOpener = new ButtonOpener();
        flagsLabel.setText(String.format("%03d",flagsCount));

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                holders[x][y] = new JPanel(new BorderLayout());

                buttons[x][y] = new JButton();
                buttons[x][y].setFont(font);
                buttons[x][y].setFocusable(false);

                labels[x][y] = new JLabel();
                labels[x][y].setHorizontalAlignment(JLabel.CENTER);
                labels[x][y].setFont(font);

                buttons[x][y].addMouseListener(buttonFlagger);
                buttons[x][y].addActionListener(buttonOpener);

                holders[x][y].add(buttons[x][y]);
                holders[x][y].setBorder(new LineBorder(color));

                innerPanel.add(holders[x][y]);
            }
        }

        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        restartButton.addActionListener(new buttonRestarter());

        buttonColor = buttons[0][0].getBackground();
        labelColor = labels[0][0].getBackground();

        setLocationRelativeTo(null);
        pack();
        setVisible(true);
    }

    private void createFiled(int[][] field, int originX, int originY) {
        int bombX;
        int bombY;
        for (int k = 0; k < maxMins; k++){
            do{
                bombX = new Random().nextInt(width);
                bombY = new Random().nextInt(height);
            }while(field[bombX][bombY] ==- 1 || (abs(bombX - originX) <= 1 && abs(bombY - originY) <= 1));
            field[bombX][bombY] = -1;
        }
        activeCells = width * height - maxMins;
        for (int i = 0; i < width; i += 1) {
            for (int j = 0; j < height; j += 1) {
                if (field[i][j] != -1) field[i][j] = bombsNeighbors(field, i, j);
            }
        }
    }

    private int bombsNeighbors(int[][] field, int x, int y) {
        int count = 0;
        int[] lineArray = getCycleBoundaries(x, true);
        int[] clmnArray = getCycleBoundaries(y, false);

        for (int k = lineArray[0]; k < lineArray[1]; k++) {
            for (int v = clmnArray[0]; v < clmnArray[1]; v++) {
                if (field[x + k][y + v] == -1) {
                        count += 1;
                    }
                }
            }
        return count;
    }

    private int[] getCycleBoundaries(int coordinate, boolean isLine){
        int[] array = {0, 0};
        int length;

        if (isLine) length = width; // для прямоугольного сапера
        else length = height;

        if (coordinate == 0){
            array[1] = 2;
        }
        else if(coordinate < (length -1) && coordinate > 0){
            array[0] = -1;
            array[1] = 2;
        }
        else{
            array[0] = -1;
            array[1] = 1;
        }
        return array;
    }

    private void openEmptyButton(int x, int y) {
        if(mineField[x][y] == 0 && buttons[x][y].getParent()!=null){
            open(x,y);
            int[] lineArray = getCycleBoundaries(x, true);
            int[] clmnArray = getCycleBoundaries(y, false);

            for (int i = lineArray[0]; i < lineArray[1]; i++) {
                for (int j = clmnArray[0]; j < clmnArray[1]; j++) {
                    if ((i != 0 || j != 0) && !buttons[x + i][y + j].getText().equals("!")) openEmptyButton(x + i, y + j);
                }
            }
        }
        if (buttons[x][y].getParent()!=null)open(x,y);
    }

    private void open(int x, int y){
        labels[x][y].setText(Integer.toString(mineField[x][y]));
        if (mineField[x][y] == 0) labels[x][y].setText("");
        if (mineField[x][y] == -1){
            labels[x][y].setText("*");
            labels[x][y].setForeground(Color.BLACK);
        }
        if (mineField[x][y] == -1 && gameStatus == GameStatus.DURING) {
            gameStatus = GameStatus.LOSE;
            labels[x][y].setBackground(Color.RED);
            labels[x][y].setOpaque(true);
        }
        holders[x][y].remove(buttons[x][y]);
        holders[x][y].add(labels[x][y]);
        if ((gameStatus == GameStatus.DURING || gameStatus == GameStatus.BEFORE) && mineField[x][y] != -1) activeCells -= 1;
        switch (mineField[x][y])
        {
            case 1: labels[x][y].setForeground(Color.BLUE);break;
            case 2: labels[x][y].setForeground(new Color(0,127,0));break;
            case 3: labels[x][y].setForeground(Color.RED);break;
            case 4: labels[x][y].setForeground(new Color(0,0,63));break;
            case 5: labels[x][y].setForeground(new Color(63,0,63));break;
            case 6: labels[x][y].setForeground(new Color(0,127,127));break;
            case 7: labels[x][y].setForeground(Color.BLACK);break;
            case 8: labels[x][y].setForeground(new Color(63,0,0));break;
        }
    }

    private void checkGameStatus(){
        switch (gameStatus){
            case LOSE:
                lose();
                timer.cancel();
                break;
            case WIN:
                win();
                timer.cancel();
                break;
        }
    }

    private class ButtonFlagger extends MouseAdapter {
        public void mousePressed(MouseEvent e) {
            JPanel p = (JPanel) (((JButton) (e.getSource())).getParent());
            int Cx = p.getX() / 40, Cy = p.getY() / 40;
            if ((gameStatus == GameStatus.BEFORE || gameStatus == GameStatus.DURING) && e.getButton() == 3) {
                if (buttons[Cx][Cy].getText().equals("!")) {
                    buttons[Cx][Cy].setText("");
                    flagsCount++;
                }
                else{
                    buttons[Cx][Cy].setText("!");
                    flagsCount--;
                }
                flagsLabel.setText(String.format("%03d",flagsCount));
            }
            checkGameStatus();
        }
    }

    private class ButtonOpener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JPanel p = (JPanel) (((JButton) (e.getSource())).getParent());
            int Cx = p.getX() / 40, Cy = p.getY() / 40;
            if(gameStatus == GameStatus.BEFORE && !buttons[Cx][Cy].getText().equals("!")){
                createFiled(mineField, Cx, Cy);
                openEmptyButton(Cx, Cy);
                timer = new Timer();
                timer.schedule(new MyTimer(), 0, 1000);
                gameStatus = GameStatus.DURING;
            }
            if (!buttons[Cx][Cy].getText().equals("!") && gameStatus == GameStatus.DURING) {
                openEmptyButton(Cx, Cy);
                if (activeCells == 0) gameStatus = GameStatus.WIN;
            }
            checkGameStatus();
            innerPanel.revalidate();
            innerPanel.repaint();
        }
    }

    private class MyTimer extends TimerTask{
        @Override
        public void run() {
            if (secondCount == 999) cancel();
            secondCount += 1;
            timerLabel.setText(String.format("%03d",secondCount));
        }
    }

    private class buttonRestarter implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            setNulls();
            gameStatus = GameStatus.BEFORE;
            timer.cancel();
            timer = new Timer();
            secondCount = 0;
            timerLabel.setText(String.format("%03d", secondCount));
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    labels[x][y].setBackground(labelColor);
                    buttons[x][y].setBackground(buttonColor);
                    if (buttons[x][y].getParent() == null) {
                        holders[x][y].remove(labels[x][y]);
                        holders[x][y].add(buttons[x][y]);
                    }
                    buttons[x][y].setText("");
                }
            }
            flagsCount = maxMins;
            flagsLabel.setText(String.format("%03d",flagsCount));
            innerPanel.revalidate();
            innerPanel.repaint();
        }
    }

    private void setNulls(){
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                mineField[i][j] = 0;
            }
        }
    }

    private void win(){
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                if (mineField[i][j] == -1) buttons[i][j].setText("!");
            }
        }
    }

    private void lose(){
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                if (mineField[i][j] == -1 && !buttons[i][j].getText().equals("!")) open(i, j);
                if (mineField[i][j] != -1 && buttons[i][j].getText().equals("!")){
                    buttons[i][j].setBackground(Color.YELLOW);
                    buttons[i][j].setOpaque(true);
                }
            }
        }
    }
}

