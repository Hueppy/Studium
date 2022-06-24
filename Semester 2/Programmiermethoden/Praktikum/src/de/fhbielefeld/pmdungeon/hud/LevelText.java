package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import de.fhbielefeld.pmdungeon.entities.Hero;
import de.fhbielefeld.pmdungeon.vorgaben.graphic.TextStage;
import de.fhbielefeld.pmdungeon.vorgaben.interfaces.IEntity;

/** Levelanzeige. */
public class LevelText implements IEntity {
  private final TextStage textStage;
  private final Hero hero;
  private final Label label;

  /** Erstellt eine Levelanzeige. */
  public LevelText(TextStage textStage, Hero hero) {
    this.textStage = textStage;
    this.hero = hero;
    this.label =
        textStage.drawText(
            "", "assets/fonts/Minecraftia-Regular.ttf", Color.WHITE, 21, 100, 1, 20, 410);
  }

  @Override
  public void update() {
    label.setText(Integer.toString(hero.getLevel()));
  }

  @Override
  public boolean deleteable() {
    return false;
  }
}
