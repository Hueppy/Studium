package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import de.fhbielefeld.pmdungeon.quests.Quest;

/** Anzeige von Quests. */
public class QuestScreen extends Screen<Quest> {
  private final Texture background = new Texture("assets/background/quest.png");
  private final Label description;

  public QuestScreen() {
    super();
    description = createLabel(60, 320);
  }

  @Override
  protected Texture getBackground() {
    return background;
  }

  @Override
  protected void drawContents(Quest object) {
    description.setText(object.getDescription());
  }
}
