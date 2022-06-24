package de.fhbielefeld.pmdungeon.hud;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.scenes.scene2d.ui.Label;
import de.fhbielefeld.pmdungeon.quests.Quest;
import java.util.ArrayList;
import java.util.List;

/** Anzeige für aktive Quests. */
public class ActiveQuestsScreen extends Screen<List<Quest>> {
  private final List<Label> labels;

  public ActiveQuestsScreen() {
    super();
    labels = new ArrayList<>();
  }

  private Label getLabel(int i) {
    if (labels.size() > i) {
      return labels.get(i);
    } else {
      Label l = null;
      for (int j = labels.size(); j <= i; j++) {
        l = createLabel(400, 450 - 20 * j);
        labels.add(l);
      }
      return l;
    }
  }

  @Override
  protected Texture getBackground() {
    return null;
  }

  @Override
  protected void drawContents(List<Quest> object) {
    for (int i = 0; i < object.size(); i++) {
      getLabel(i).setText(object.get(i).getDescription());
    }
    for (int i = object.size(); i < labels.size(); i++) {
      getLabel(i).setText("");
    }
  }
}
