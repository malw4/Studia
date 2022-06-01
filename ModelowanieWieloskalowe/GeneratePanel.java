package mod.panels;

import mod.JPane;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class GeneratePanel extends JPanel {
    public int generationType;
    public JPane canvas;

    String[] generationTypesNames = {"Wybierz Stan", "Jednorodne", "Z promieniem", "Losowe", "Wyklikanie"};
    private JComboBox statesChoice = new JComboBox(generationTypesNames);

    public GeneratePanel(JPane canv) {
        canvas = canv;
        setPreferredSize(new Dimension(200, 200));
        add(statesChoice);
        initCombo();
    }

    void initCombo() {
        statesChoice.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int stan = statesChoice.getSelectedIndex();
                int a = 0, b = 0;
                if (stan == 1) {
                    String liczbA = JOptionPane.showInputDialog("Podaj liczbę punktow w rzędzie:");
                    a = (Integer.parseInt(liczbA));
                    String liczbB = JOptionPane.showInputDialog("Podaj liczbę punktow w kolumnie:");
                    b = (Integer.parseInt(liczbB));
                    canvas.zad.generateUniform(a, b);
                } else if (stan == 2) {
                    String liczbA = JOptionPane.showInputDialog("Podaj liczbę punktow:");
                    a = (Integer.parseInt(liczbA));
                    String liczbB = JOptionPane.showInputDialog("Podaj promien:");
                    b = (Integer.parseInt(liczbB));
                    canvas.zad.generateRadius(a, b);
                } else if (stan == 3) {
                    String liczb = JOptionPane.showInputDialog("Podaj liczbę punktow do stworzenia:");
                    a = (Integer.parseInt(liczb));
                    canvas.zad.generateRandom(a);
                    canvas.repaint();
                } else if (stan == 4) {
                    canvas.addMouseListener(new MouseListener() {
                        @Override
                        public void mouseClicked(MouseEvent e) {
                        }

                        @Override
                        public void mousePressed(MouseEvent e) {
                        }

                        @Override
                        public void mouseReleased(MouseEvent e) {
                            int x = e.getX() / canvas.cellSize;
                            int y = e.getY() / canvas.cellSize;
                            canvas.zad.generateMyself(x, y);
                            canvas.repaint();
                        }

                        @Override
                        public void mouseEntered(MouseEvent e) {
                        }

                        @Override
                        public void mouseExited(MouseEvent e) {
                        }
                    });
                }
                canvas.repaint();
            }
        });
    }
}
