package mod.panels;

import mod.JPane;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FieldSizePanel extends JPanel {

    public JPane canvas;

    public int initialWidth = 180;
    public int initialHeight = 150;
    SpinnerModel sizeWSpinnerModel = new SpinnerNumberModel(initialWidth, 0, 1000, 1);
    SpinnerModel sizeHSpinnerModel = new SpinnerNumberModel(initialHeight, 0, 1000, 1);
    private JSpinner spinWidth = new JSpinner(sizeWSpinnerModel);
    private JSpinner spinHeight = new JSpinner(sizeHSpinnerModel);
    private JButton changeSizeButton = new JButton("Change size");

    public FieldSizePanel(JPane canv) {
        canvas = canv;
        setPreferredSize(new Dimension(200, 200));
        add(spinWidth);
        add(spinHeight);
        add(changeSizeButton);
        initButton();
    }

    void initButton() {
        changeSizeButton.setSize(200, 20);
        changeSizeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int width = (int) spinWidth.getValue();
                int height = (int) spinHeight.getValue();
                canvas.setNewZad(width, height);
            }
        });
    }
}
