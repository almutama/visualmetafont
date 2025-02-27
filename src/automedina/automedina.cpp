/*
 * Copyright (c) 2015-2020 Amine Anane. http: //digitalkhatt/license
 * This file is part of DigitalKhatt.
 *
 * DigitalKhatt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * DigitalKhatt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public License
 * along with DigitalKhatt. If not, see
 * <https: //www.gnu.org/licenses />.
*/

#include "automedina.h"
#include "qstring.h"
#include "Subtable.h"
#include "Lookup.h"
#include "font.hpp"
#include "GlyphVis.h"
#include <algorithm>
#include "qregularexpression.h"
#include "defaultmarkpositions.h"
#include "metafont.h"
#include "qdebug.h"


using namespace std;

CalcAnchor  Automedina::getanchorCalcFunctions(QString functionName, Subtable* subtable) {
  if (functionName == "defaultmarkabovemark") {
    return Defaultmarkabovemark(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaultopmarkanchor") {
    return Defaultopmarkanchor(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaultmarkbelowmark") {
    return Defaultmarkbelowmark(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaullowmarkanchor") {
    return Defaullowmarkanchor(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaultwaqfmarkabovemark") {
    return Defaulwaqftmarkabovemark(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaultbaseanchorforlow") {
    return Defaulbaseanchorforlow(*this, *(MarkBaseSubtable*)(subtable));
  }
  else if (functionName == "defaulbaseanchorfortop") {
    return Defaulbaseanchorfortop(*this, *(MarkBaseSubtable*)(subtable));
  }

  else if (functionName == "joinedsmalllettersbaseanchor") {
    return Joinedsmalllettersbaseanchor(*this, *(MarkBaseSubtable*)(subtable));
  }
}

Automedina::Automedina(OtLayout* layout, MP mp, bool extended) :glyphs{ layout->glyphs }, m_layout{ layout }, mp{ mp }, extended{ extended } {

  //m_metafont = layout->m_font;
  classes["marks"] = {
      "onedotup",
      "onedotdown",
      "twodotsup",
      "twodotsdown",
      "three_dots",
      "fathatanidgham",
      "kasratanidgham",
      "dammatanidgham",
      "fatha",
      "damma",
      "kasra",
      "shadda",
      "headkhah",
      "sukun",
      "dammatan",
      "maddahabove",
      "fathatan",
      "kasratan",
      "smallalef",
      "smallalef.replacement",
      "smallalef.joined",
      "meemiqlab",
      "smalllowmeem",
      "smallhighyeh",
      "smallhighwaw",
      "wasla",
      "hamzaabove",
      "hamzaabove.lamalef",
      "hamzaabove.joined",
      "hamzabelow",
      "smallhighroundedzero",
      "rectangularzero",
      "smallhighseen",
      "smalllowseen",
      "smallhighnoon",
      "waqf.meem",
      "waqf.lam",
      "waqf.qaf",
      "waqf.jeem",
      "waqf.sad",
      "waqf.smallhighthreedots",
      "roundedfilledhigh",
      "roundedfilledlow",
      "space.ii"
  };

  classes["topmarks"] = {
    //"onedotup",
    //"twodotsup",
    //"three_dots",
    "fathatanidgham",
    "dammatanidgham",
    "fatha",
    "damma",
    "shadda",
    "headkhah",
    "sukun",
    "dammatan",
    "maddahabove",
    "fathatan",
    "smallalef",
    "smallalef.replacement",
    "smallalef.joined",
    "meemiqlab",
    "smallhighyeh",
    "smallhighwaw",
    "wasla",
    "hamzaabove",
    "hamzaabove.joined",
    //"hamzaabove.lamalef",
    "smallhighroundedzero",
    "rectangularzero",
    "smallhighseen",
    "smallhighnoon",
    "roundedfilledhigh",
    "hamzaabove.joined",
  };

  classes["lowmarks"] = {
    //"onedotdown",
    //"twodotsdown",
    "kasratanidgham",
    "kasra",
    "kasratan",
    "hamzabelow",
    "smalllowseen",
    "roundedfilledlow"
  };

  classes["kasras"] = {
      "kasratanidgham",
      "kasra",
      "kasratan"
  };

  classes["waqfmarks"] = {
      "waqf.meem",
      "waqf.lam",
      "waqf.qaf",
      "waqf.jeem",
      "waqf.sad",
      "waqf.smallhighthreedots"
  };

  classes["dotmarks"] = {
      "onedotup",
      "onedotdown",
      "twodotsup",
      "twodotsdown",
      "three_dots"
  };

  classes["topdotmarks"] = {
      "onedotup",
      "twodotsup",
      "three_dots"
  };

  classes["downdotmarks"] = {
      "onedotdown",
      "twodotsdown"
  };

  classes["digits"] = {
      "zeroindic",
      "oneindic",
      "twoindic",
      "threeindic",
      "fourindic",
      "fiveindic",
      "sixindic",
      "sevenindic",
      "eightindic",
      "nineindic"
  };

  initchar = {
    "behshape" ,
    //"teh" ,
    //"tehmarbuta" ,
    //"theh" ,
    //"jeem" ,
    "hah" ,
    //"khah" ,
    //"dal" ,
    //"thal" ,
    //"reh" ,
    //"zain" ,
    "seen" ,
    //"sheen" ,
    "sad" ,
    //"dad" ,
    "tah" ,
    //"zah" ,
    "ain" ,
    //"ghain" ,
    "fehshape" ,
    //"qaf" ,
    "kaf" ,
    "lam" ,
    "meem" ,
    //"noon" ,
    "heh" ,
    //"waw" ,
    //"yeh" ,
    //"yehwithoutdots" ,
    //"alefmaksura"
  };

  medichar = {
    //"alef" ,
    "behshape" ,
    //"teh" ,
    //"tehmarbuta" ,
    //"theh" ,
    //"jeem" ,
    "hah" ,
    //"khah" ,
    //"dal" ,
    //"thal" ,
    //"reh" ,
    //"zain" ,
    "seen" ,
    //"sheen" ,
    "sad" ,
    //"dad" ,
    "tah" ,
    //"zah" ,
    "ain" ,
    //"ghain" ,
    "fehshape" ,
    //"qaf" ,
    "kaf" ,
    "lam" ,
    "meem" ,
    //"noon" ,
    "heh" ,
    //"waw" ,
    //"yeh" ,
    //"yehwithoutdots" ,
    //"alefmaksura"
  };

  addchars();

  generateGlyphs();

  //setAnchorCalcFunctions();

 
  layout->expandableGlyphs["behshape.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["behshape.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["kaf.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["kaf.fina.afterlam.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["noon.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["noon.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["noon.fina.afterbeh.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["alefmaksura.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["yehshape.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["yehshape.fina.afterbeh.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["yehshape.fina.ii.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["yehshape.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["sad.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["sad.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["seen.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["seen.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["feh.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["feh.fina.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["qaf.isol.expa"] = { 5,0,0,0 };
  layout->expandableGlyphs["qaf.fina.expa"] = { 5,0,0,0 };
  /*
  layout->expandableGlyphs["behshape.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["hah.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["seen.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["sad.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["tah.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["ain.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["fehshape.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["kaf.init"] = { 5,-1.2,0,0 };
  layout->expandableGlyphs["kaf.init.ii"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["lam.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["meem.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["heh.init"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["kaf.init.ii"] = { 5,-1.0,0.0,0.0 };

  layout->expandableGlyphs["heh.medi"] = { 5,-1.0,0,0 };
  layout->expandableGlyphs["behshape.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["behshape.medi.beforeseen"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["behshape.medi.beforenoon"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["hah.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["hah.medi.afterbeh"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["hah.medi.lam_hah"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["hah.medi.beforemeem"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["seen.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["sad.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["tah.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["ain.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["fehshape.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["kaf.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["lam.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["lam.medi.afterkaf"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["meem.medi"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["meem.medi.afterhah"] = { 5,-1.0,5,-1.0 };
  layout->expandableGlyphs["seen.medi.basmala"] = { 20,0,0,0 };

  layout->expandableGlyphs["alef.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["hah.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["feh.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["meem.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["behshape.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["qaf.fina"] = { 0.0,0.0,5,-1.0 };
  layout->expandableGlyphs["noon.fina.basmala"] = { 10.0,0.0,0,-1.0 };*/

  layout->expandableGlyphs["behshape.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["hah.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["seen.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["sad.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["tah.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["ain.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["fehshape.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["kaf.init"] = { 5,-1.2,0,0 };
  layout->expandableGlyphs["kaf.init.ii"] = { 5,-1.5,0,0 };
  layout->expandableGlyphs["lam.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["meem.init"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["heh.init"] = { 5,-0.5,0,0 };

  layout->expandableGlyphs["heh.medi"] = { 5,-0.5,0,0 };
  layout->expandableGlyphs["behshape.medi"] = { 12,-0.5,12,-0.5 };
  layout->expandableGlyphs["behshape.medi.ii"] = { 9,-1,9,-1 };
  layout->expandableGlyphs["behshape.medi.beforeseen"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["hah.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["hah.medi.afterbeh"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["hah.medi.lam_hah"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["hah.medi.beforemeem"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["seen.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["sad.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["tah.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["ain.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["fehshape.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["kaf.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["lam.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["lam.medi.afterkaf"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["meem.medi"] = { 5,-0.5,5,-0.5 };
  layout->expandableGlyphs["meem.medi.afterhah"] = { 5,-1.0,5,-0.5 };
  layout->expandableGlyphs["behshape.medi.beforenoon"] = { 0,0,0,-0.4 };
  layout->expandableGlyphs["seen.medi.basmala"] = { 20,0,0,0 };
  layout->expandableGlyphs["kaf.medi.ii"] = { 5,-0.5,5,-0.5 };
  

  layout->expandableGlyphs["alef.fina"] = { 0.0,0.0,5,-0.3 };
  layout->expandableGlyphs["dal.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["heh.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["hah.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["feh.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["meem.fina"] = { 0.0,0.0,5,-0.3 };
  layout->expandableGlyphs["meem.fina.ii"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["behshape.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["qaf.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["lam.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["kaf.fina"] = { 0.0,0.0,5,-0.5 };
  layout->expandableGlyphs["noon.fina.basmala"] = { 10.0,0.0,0,-0.5 };

  layout->expandableGlyphs["hah.init.iii"] = { 9.0,0.0,0,0 };
  layout->expandableGlyphs["seen.init.kii"] = { 9.0,0.0,0,0 };
  layout->expandableGlyphs["sad.init.kii"] = { 9.0,0.0,0,0 };
  layout->expandableGlyphs["alef.fina.ii"] = { 0.0,0.0,9,-1 };
  layout->expandableGlyphs["heh.fina.ii"] = { 0.0,0.0,9,-1 };
  layout->expandableGlyphs["dal.fina.kii"] = { 0.0,0.0,9,-1 };
  

  layout->expandableGlyphs["fatha"] = { 12,-1.0,0,0 };
  layout->expandableGlyphs["kasra"] = { 12,-1.0,0,0 };
  layout->expandableGlyphs["space"] = { 4.0,-0.5,0.0,0.0 };
  
}

void Automedina::generateGlyphs() {

  mp_run_data* _mp_results = mp_rundata(mp);
  mp_edge_object* edges = _mp_results->edges;

  glyphs.clear();

  while (edges) {

    auto name = QString(edges->charname);

    if (name != "alternatechar") {
      GlyphVis& glyph = *glyphs.insert(name, GlyphVis(m_layout, edges));


      m_layout->glyphNamePerCode[glyph.charcode] = glyph.name;
      m_layout->glyphCodePerName[glyph.name] = glyph.charcode;
      m_layout->unicodeToGlyphCode.insert(glyph.charcode, glyph.charcode);

      //if (glyph.name.contains("space")) {

      //}
      //else
      if (!classes["marks"].contains(glyph.name)) {
        classes["bases"].insert(glyph.name);
        m_layout->glyphGlobalClasses[glyph.charcode] = OtLayout::BaseGlyph;
      }
      else {
        m_layout->glyphGlobalClasses[glyph.charcode] = OtLayout::MarkGlyph;
      }

      //uint totalAnchors = getTotalAnchors(mp, glyph.charcode);
      /*
            if (edges->numAnchors > 10) {
                    throw "error";
    }*/

      for (int i = 0; i < edges->numAnchors; i++) {
        AnchorPoint anchor = edges->anchors[i];
        if (anchor.anchorName) {
          switch (anchor.type)
          {
          case 1:
            markAnchors[anchor.anchorName][glyph.charcode] = QPoint(anchor.x, anchor.y);
            break;
          case 2:
            entryAnchors[anchor.anchorName][glyph.charcode] = QPoint(anchor.x, anchor.y);
            break;
          case 3:
            exitAnchors[anchor.anchorName][glyph.charcode] = QPoint(anchor.x, anchor.y);
          case 4:
            entryAnchorsRTL[anchor.anchorName][glyph.charcode] = QPoint(anchor.x, anchor.y);
            break;
          case 5:
            exitAnchorsRTL[anchor.anchorName][glyph.charcode] = QPoint(anchor.x, anchor.y);
          default:
            break;
          }
        }
      }
    }



    edges = edges->next;
  }


  auto ayaGlyph = glyphs["endofaya"];

  int ayacharcode = AyaNumberCode;

  for (int i = 1; i <= 286; i++) {

    QString name = QString("aya%1").arg(i);

    // Amine very temporary for test
    auto& glyph = *glyphs.insert(name, ayaGlyph);

    glyph.name = name;
    glyph.charcode = ayacharcode++;
#ifndef DIGITALKHATT_WEBLIB
    glyph.refresh(glyphs);
#endif

    m_layout->glyphNamePerCode.insert(glyph.charcode, glyph.name);
    m_layout->glyphCodePerName.insert(glyph.name, glyph.charcode);

    m_layout->glyphGlobalClasses.insert(glyph.charcode, OtLayout::LigatureGlyph);
  }


  /*
         "0622": [ "alef.isol", "maddahabove" ],
        "0623": [ "alef.isol", "hamzaabove" ],
        "0624": [ "waw.isol", "hamzaabove" ],
        "0625": [ "alef.isol", "hamzabelow" ],
        "0626": [ "alefmaksura.isol", "hamzaabove" ],
        "0628": [ "behshape.isol", "onedotdown" ],
        "0629": [ "heh.isol", "twodotsup" ],
        "062A": [ "behshape.isol", "twodotsup" ],
        "062B": [ "behshape.isol", "three_dots" ],
        "062C": [ "hah.isol", "onedotdown" ],
        "062E": [ "hah.isol", "onedotup" ],
        "0630": [ "dal.isol", "onedotup" ],
        "0632": [ "reh.isol", "onedotup" ],
        "0634": [ "seen.isol", "three_dots" ],
        "0636": [ "sad.isol", "onedotup" ],
        "0638": [ "tah.isol", "onedotup" ],
        "063A": [ "ain.isol", "onedotup" ],
        "0671": [ "alef.isol", "wasla" ]*/


  auto addFake = [this](QString glyphName, quint16 unicode, quint16 codechar) {
    auto code = unicode; //codechar; //layout.glyphNamePerCode.lastKey();
    GlyphVis& glyph = *glyphs.insert(glyphName, GlyphVis());
    glyph.name = glyphName;
    glyph.charcode = code;

    m_layout->glyphNamePerCode[glyph.charcode] = glyph.name;
    m_layout->glyphCodePerName[glyph.name] = glyph.charcode;
    m_layout->unicodeToGlyphCode.insert(unicode, glyph.charcode);


  };
  addFake("alef.maddahabove.isol", 0x0622, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("alef.hamzaabove.isol", 0x0623, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("waw.hamzaabove.isol", 0x0624, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("alef.hamzabelow.isol", 0x0625, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("alefmaksura.hamzaabove.isol", 0x0626, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("behshape.onedotdown.isol", 0x0628, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("heh.twodotsup.isol", 0x0629, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("behshape.twodotsup.isol", 0x062A, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("behshape.three_dots.isol", 0x062B, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("hah.onedotdown.isol", 0x062C, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("hah.onedotup.isol", 0x062E, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("dal.onedotup.isol", 0x0630, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("reh.onedotup.isol", 0x0632, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("seen.three_dots.isol", 0x0634, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("sad.onedotup.isol", 0x0636, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("tah.onedotup.isol", 0x0638, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("ain.onedotup.isol", 0x063A, m_layout->glyphNamePerCode.lastKey() + 1);
  addFake("alef.wasla.isol", 0x0671, m_layout->glyphNamePerCode.lastKey() + 1);

  m_layout->glyphs = glyphs;


}

Lookup* Automedina::getLookup(QString lookupName) {

  if (lookupName == "defaultmarkpositioncpp") {
    return defaultmarkposition();
  }
  else if (lookupName == "defaultwaqfmarktobase") {
    return defaultwaqfmarktobase();
  }
  else if (lookupName == "forsmalllalef") {
    return forsmalllalef();
  }
  else if (lookupName == "forhamza") {
    return forhamza();
  }
  else if (lookupName == "forheh") {
    return forheh();
  }
  else if (lookupName == "forwaw") {
    return forwaw();
  }
  else if (lookupName == "leftrightcursive") {
    return leftrightcursive();
  }
  else if (lookupName == "rehwawcursive") {
    return rehwawcursive();
  }
  else if (lookupName == "ligaturecursive") {
    return ligaturecursive();
  }
  else if (lookupName == "defaultdotmarks") {
    return defaultdotmarks();
  }
  else if (lookupName == "pointmarks") {
    return pointmarks();
  }
  else if (lookupName == "defaultwaqfmarkabovemarkprecise") {
    return defaultwaqfmarkabovemarkprecise();
  }
  else if (lookupName == "defaultmarkdotmarks") {
    return defaultmarkdotmarks();
  }
  else if (lookupName == "defaultmkmk") {
    return defaultmkmk();
  }
  else if (lookupName == "ayanumbers") {
    return ayanumbers();
  }
  else if (lookupName == "ayanumberskern") {
    return ayanumberskern();
  }
  else if (lookupName == "shrinkstretchlt") {
    return shrinkstretchlt();
  }
  else if (lookupName == "lowmarkafterwawandreh") {
    return lowmarkafterwawandreh();
  }
  else if (lookupName == "tajweedcolorcpp") {
    return tajweedcolorcpp();
  }
  else if (lookupName == "forsmallhighwaw") {
    return forsmallhighwaw();
  }



  return NULL;
}

Lookup* Automedina::rehwawcursive() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "rehwawcursive";
  lookup->feature = "curs";
  lookup->type = Lookup::cursive;
  lookup->flags = Lookup::Flags::IgnoreMarks;

  class CustomCursiveSubtable : public CursiveSubtable {
  public:
    CustomCursiveSubtable(Lookup* lookup) : CursiveSubtable(lookup) {}

    virtual QPoint calculateEntry(GlyphVis* originalglyph, GlyphVis* extendedglyph, QPoint defaultEntry) {

      QPoint entry = entryParameters[originalglyph->charcode];

      entry += QPoint(extendedglyph->width, 0);

      return entry;

    }

  };

  CursiveSubtable* rehwawisol = new CustomCursiveSubtable(lookup);
  lookup->subtables.append(rehwawisol);
  rehwawisol->name = "rehwawisol";

  CursiveSubtable* rehwawfina = new CustomCursiveSubtable(lookup);
  lookup->subtables.append(rehwawfina);
  rehwawfina->name = "rehwawfina";

  CursiveSubtable* rehfinaafterbehshape = new CursiveSubtable(lookup);
  lookup->subtables.append(rehfinaafterbehshape);
  rehfinaafterbehshape->name = "rehfinaafterbehshape";
  rehfinaafterbehshape->anchors[glyphs["reh.fina.afterbehshape"].charcode].exit = QPoint(0, 0);

  CursiveSubtable* rehfinaafterseen = new CursiveSubtable(lookup);
  lookup->subtables.append(rehfinaafterseen);
  rehfinaafterseen->name = "rehfinaafterseen";
  rehfinaafterseen->anchors[glyphs["reh.fina.afterseen"].charcode].exit = QPoint(0, 0);




  auto glyphcodes = m_layout->classtoUnicode("reh.isol|waw.isol");

  for (auto glyphcode : glyphcodes) {
    rehwawisol->anchors[glyphcode].exit = QPoint(0, 0);
  }

  glyphcodes = m_layout->classtoUnicode("reh.fina$|waw.fina$");

  for (auto glyphcode : glyphcodes) {
    rehwawfina->anchors[glyphcode].exit = QPoint(0, 0);
  }



  glyphcodes = m_layout->classtoUnicode("isol|init"); //"((?<!reh|waw)[.]isol)|init"

  for (auto glyphcode : glyphcodes) {
    QString glyphName = m_layout->glyphNamePerCode[glyphcode];
    auto& glyph = glyphs[glyphName];
    bool includeGlyph = true;
    for (auto anchors : exitAnchorsRTL) {
      if (anchors.contains(glyphcode)) {
        includeGlyph = false;
        break;
      }
    }

    if (includeGlyph) {
      rehwawisol->anchors[glyphcode].entry = QPoint(glyph.width, 0);
      rehwawfina->anchors[glyphcode].entry = QPoint(glyph.width, 0);
      rehfinaafterbehshape->anchors[glyphcode].entry = QPoint(glyph.width, 0);
      rehfinaafterseen->anchors[glyphcode].entry = QPoint(glyph.width, 0);
    }

  }

  return lookup;

}
Lookup* Automedina::leftrightcursive() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "leftrightcursive";
  lookup->feature = "curs";
  lookup->type = Lookup::cursive;
  lookup->flags = 0;
  lookup->flags = lookup->flags | Lookup::Flags::RightToLeft | Lookup::Flags::IgnoreMarks;

  struct Impl : CursiveSubtable
  {
    Impl(Lookup* lookup) : CursiveSubtable{ lookup } {}

    virtual optional<QPoint> getEntry(quint16 glyph_id, double lefttatweel, double righttatweel) override {

      if (lefttatweel == 0 && righttatweel == 0) {
        return CursiveSubtable::getEntry(glyph_id, 0, 0);
      }

      auto glyphName = this->getNameFromCode(glyph_id);

      GlyphVis* glyph = &this->m_layout->glyphs[glyphName];

      GlyphParameters parameters{};

      parameters.lefttatweel = lefttatweel;
      parameters.righttatweel = righttatweel;

      glyph = glyph->getAlternate(parameters);

      return glyph->rightAnchor;

    }

    virtual optional<QPoint> getExit(quint16 glyph_id, double lefttatweel, double righttatweel) override {

      if (lefttatweel == 0 && righttatweel == 0) {
        return CursiveSubtable::getExit(glyph_id, 0, 0);
      }

      auto glyphName = this->getNameFromCode(glyph_id);

      GlyphVis* glyph = &this->m_layout->glyphs[glyphName];

      GlyphParameters parameters{};

      parameters.lefttatweel = lefttatweel;
      parameters.righttatweel = righttatweel;

      glyph = glyph->getAlternate(parameters);

      return glyph->leftAnchor;

    }
  };


  CursiveSubtable* newsubtable = new Impl(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "leftrightcursive";

  for (auto& glyph : glyphs) {
    if (glyph.leftAnchor || glyph.rightAnchor) {
      newsubtable->anchors[glyph.charcode].entry = glyph.rightAnchor;
      newsubtable->anchors[glyph.charcode].exit = glyph.leftAnchor;
    }
  }

  /*
        CursiveSubtable* leftrightcursivenonjoining = new CursiveSubtable(lookup);
        lookup->subtables.append(leftrightcursivenonjoining);

        leftrightcursivenonjoining->name = "leftrightcursivenonjoining";

        for (auto& firstglyph : glyphs) {
                if (firstglyph.name.contains("isol")) {
                        for (auto& secondglyph : glyphs) {
                                if (secondglyph.name.contains("init")) {
                                        leftrightcursivenonjoining->anchors[firstglyph.charcode].exit = QPoint{ 0,0 };
                                        leftrightcursivenonjoining->anchors[secondglyph.charcode].entry = QPoint{ (int)secondglyph.width,0 };
                                }
                        }

                }
        }*/

  return lookup;

}
Lookup* Automedina::ligaturecursive() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "ligaturecursive";
  lookup->feature = "curs";
  lookup->type = Lookup::cursive;
  lookup->flags = 0;
  //lookup->flags = lookup->flags | Lookup::Flags::RightToLeft | Lookup::Flags::IgnoreMarks;
  lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;


  for (auto it = entryAnchors.constBegin(); it != entryAnchors.constEnd(); ++it) {
    QString cursiveName = it.key();
    auto entries = it.value();
    auto exits = exitAnchors[cursiveName];

    CursiveSubtable* newsubtable = new CursiveSubtable(lookup);
    lookup->subtables.append(newsubtable);
    newsubtable->name = cursiveName;

    for (auto anchor = entries.constBegin(); anchor != entries.constEnd(); ++anchor) {
      newsubtable->anchors[anchor.key()].entry = anchor.value();
    }

    for (auto anchor = exits.constBegin(); anchor != exits.constEnd(); ++anchor) {
      newsubtable->anchors[anchor.key()].exit = anchor.value();
    }
  }

  m_layout->addLookup(lookup);

  lookup = new Lookup(m_layout);
  lookup->name = "ligaturecursiveRTL";
  lookup->feature = "curs";
  lookup->type = Lookup::cursive;
  lookup->flags = 0;
  lookup->flags = lookup->flags | Lookup::Flags::RightToLeft | Lookup::Flags::IgnoreMarks;

  for (auto it = entryAnchorsRTL.constBegin(); it != entryAnchorsRTL.constEnd(); ++it) {
    QString cursiveName = it.key();
    auto entries = it.value();
    auto exits = exitAnchorsRTL[cursiveName];

    CursiveSubtable* newsubtable = new CursiveSubtable(lookup);
    lookup->subtables.append(newsubtable);
    newsubtable->name = "ligaturecursiveRTL";

    for (auto anchor = entries.constBegin(); anchor != entries.constEnd(); ++anchor) {
      newsubtable->anchors[anchor.key()].entry = anchor.value();
    }

    for (auto anchor = exits.constBegin(); anchor != exits.constEnd(); ++anchor) {
      newsubtable->anchors[anchor.key()].exit = anchor.value();
    }
  }


  return lookup;



  /*
        int leftbearing = 100;

        if (glyphs["alefmaksura.fina.ii"]->anchors.contains("yehcursive1")) {
                //newsubtable->anchors[m_layout->glyphCodePerName["alefmaksura.fina.ii"]].entry = QPoint(400 + leftbearing - 24, 62);
                newsubtable->anchors[m_layout->glyphCodePerName["alefmaksura.fina.ii"]].entry = glyphs["alefmaksura.fina.ii"]->anchors["yehcursive1"];
        }

        newsubtable->anchors[m_layout->glyphCodePerName["yeh.fina.ii"]].entry = glyphs["yeh.fina.ii"]->anchors["yehcursive1"];

        if (glyphs["lam.medi.beforeyeh"]->anchors.contains("yehcursive1")) {
                //newsubtable->anchors[m_layout->glyphCodePerName["lam.medi.beforeyeh"]].exit = QPoint(2, -79);
                newsubtable->anchors[m_layout->glyphCodePerName["lam.medi.beforeyeh"]].exit = glyphs["lam.medi.beforeyeh"]->anchors["yehcursive1"];
        }

        if (glyphs["feh.init.yeh"]->anchors.contains("yehcursive1")) {
                newsubtable->anchors[m_layout->glyphCodePerName["feh.init.yeh"]].exit = glyphs["feh.init.yeh"]->anchors["yehcursive1"];
        }*/



}
Lookup* Automedina::defaultmarkposition() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultmarkposition";
  lookup->feature = "mark";
  lookup->type = Lookup::mark2base;
  lookup->flags = 0;

  auto topmarks = classes["topmarks"];

  topmarks.remove("smallalef");
  topmarks.remove("smallalef.joined");
  topmarks.remove("smallalef.replacement");
  topmarks.remove("smallhighyeh");
  topmarks.remove("smallhighwaw");
  topmarks.remove("smallhighnoon");
  topmarks.remove("roundedfilledhigh");
  topmarks.remove("hamzaabove");
  topmarks.remove("hamzaabove.joined");
  topmarks.remove("wasla");
  topmarks.remove("maddahabove");
  topmarks.remove("smallhighseen");
  topmarks.remove("shadda");

  auto lowmarks = classes["lowmarks"];
  lowmarks.remove("hamzabelow");
  lowmarks.remove("smalllowseen");


  //meem.fina.afterkaf

  MarkBaseSubtable* newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "meemfinaafterkaf";
  newsubtable->base = { "meem.fina.afterkaf" };
  newsubtable->classes["sukun"].mark = { "sukun" };
  newsubtable->classes["sukun"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["sukun"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //tah
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "tah";
  newsubtable->base = { "^tah" };

  newsubtable->classes["fathadamma"].mark = { "fatha", "damma","shadda", "sukun" };
  newsubtable->classes["fathadamma"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["fathadamma"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  newsubtable->classes["fathatandammatan"].mark = { "fathatan", "dammatan" };
  newsubtable->classes["fathatandammatan"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["fathatandammatan"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  newsubtable->classes["idgham"].mark = { "fathatanidgham", "dammatanidgham" };
  newsubtable->classes["idgham"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["idgham"].markfunction = Defaultopmarkanchor(*this, *newsubtable);


  //default
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "defaultmarkposition";
  newsubtable->base = { "bases" };
  newsubtable->classes["topmarks"].mark = topmarks;
  newsubtable->classes["topmarks"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["topmarks"].markfunction = Defaultopmarkanchor(*this, *newsubtable);


  newsubtable->classes["lowmarks"].mark = lowmarks;
  newsubtable->classes["lowmarks"].basefunction = Defaulbaseanchorforlow(*this, *newsubtable);
  newsubtable->classes["lowmarks"].markfunction = Defaullowmarkanchor(*this, *newsubtable);

  /*
        newsubtable->classes["shadda"].mark = { "shadda" };
        newsubtable->classes["shadda"].basefunction = new Defaulbaseanchorforsmallalef(*this, *newsubtable);
        newsubtable->classes["shadda"].markfunction = new Defaultopmarkanchor(*this, *newsubtable);*/

  newsubtable->classes["smallletters"].mark = { "smallalef.joined","smallhighwaw","hamzaabove.joined" };
  newsubtable->classes["smallletters"].basefunction = Defaulbaseanchorforsmallalef(*this, *newsubtable);
  newsubtable->classes["smallletters"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //default
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);
  newsubtable->name = "smallhighyeh";
  newsubtable->base = { "bases" }; // TODO minimize

  newsubtable->classes["smallhighyeh"].mark = { "smallhighyeh" };
  newsubtable->classes["smallhighyeh"].basefunction = Defaulbaseanchorforsmallalef(*this, *newsubtable);
  newsubtable->classes["smallhighyeh"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //shadda

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "shadda";
  newsubtable->base = { "bases" };
  newsubtable->classes["shadda"].mark = { "shadda" };
  newsubtable->classes["shadda"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["shadda"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //maddahabove

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "maddahabove";
  newsubtable->base = { "bases" };
  newsubtable->classes["maddahabove"].mark = { "maddahabove" };
  newsubtable->classes["maddahabove"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["maddahabove"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //hamzaabove

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "hamzaabove";
  newsubtable->base = { "alef|waw|yehshape|behshape" };
  newsubtable->classes["hamzaabove"].mark = { "hamzaabove" };
  newsubtable->classes["hamzaabove"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["hamzaabove"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //smallalef.replacement

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "smallalefreplacement";
  newsubtable->base = { "alef|waw|yehshape|behshape" };
  newsubtable->classes["smallalefreplacement"].mark = { "smallalef.replacement" };
  newsubtable->classes["smallalefreplacement"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["smallalefreplacement"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //roundedfilledhigh

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "roundedfilledhigh";
  newsubtable->base = { "alef[.]isol.*|meem[.]init.*" };
  newsubtable->classes["roundedfilledhigh"].mark = { "roundedfilledhigh" };
  newsubtable->classes["roundedfilledhigh"].basefunction = Defaulbaseanchorforsmallalef(*this, *newsubtable);
  newsubtable->classes["roundedfilledhigh"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //smallhighnoon
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "smallhighnoon";
  newsubtable->base = { "behshape[.]init.*" };
  newsubtable->classes["smallhighnoon"].mark = { "smallhighnoon" };
  newsubtable->classes["smallhighnoon"].basefunction = Defaulbaseanchorforsmallalef(*this, *newsubtable);
  newsubtable->classes["smallhighnoon"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //smallhighseen
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "smallhighseen";
  newsubtable->base = { "sad[.]medi|^alef.fina|^heh.fina|^lam.fina|^noon.fina" };
  newsubtable->classes["smallhighseen"].mark = { "smallhighseen" };
  newsubtable->classes["smallhighseen"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["smallhighseen"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //hamzaabove.lamalef
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "hamzaabove.lamalef";
  newsubtable->base = { "lam.init.lamalef","^lam.medi.laf" };
  newsubtable->classes["hamzaabove"].mark = { "hamzaabove.lamalef" };
  newsubtable->classes["hamzaabove"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["hamzaabove"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //hamzabelow
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "hamzabelow";
  newsubtable->base = { "^alef[.]" };
  newsubtable->classes["hamzabelow"].mark = { "hamzabelow" };
  //newsubtable->classes["hamzabelow"].basefunction  = nullptr;//;new Defaulbaseanchorforlow(*this, *newsubtable);
  //newsubtable->classes["hamzabelow"].markfunction = nullptr; // new Defaullowmarkanchor(*this, *newsubtable);

  //wasla
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "wasla";
  newsubtable->base = { "^alef[.]" };
  newsubtable->classes["wasla"].mark = { "wasla" };
  newsubtable->classes["wasla"].basefunction = Defaulbaseanchorfortop(*this, *newsubtable);
  newsubtable->classes["wasla"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  //smalllowseen
  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "smalllowseen";
  newsubtable->base = { "^sad[.]medi" };
  newsubtable->classes["smalllowseen"].mark = { "smalllowseen" };
  newsubtable->classes["smalllowseen"].basefunction = Defaulbaseanchorforlow(*this, *newsubtable);
  newsubtable->classes["smalllowseen"].markfunction = Defaullowmarkanchor(*this, *newsubtable);


  return lookup;



}
Lookup* Automedina::defaultwaqfmarktobase() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultwaqfmarktobase";
  lookup->feature = "mark";
  lookup->type = Lookup::mark2base;


  auto basefunction = [this](QString glyphName, QString className, QPoint adjust, double, double) -> QPoint {
    GlyphVis& curr = glyphs[glyphName];

    int height = std::max((int)curr.height + spacebasetotopmark, minwaqfhigh);
    int width = 0; // curr.bbox.llx;


    width = width + adjust.x();
    height = height + adjust.y();

    return QPoint(width, height);
  };

  auto markfunction = [this](QString glyphName, QString className, QPoint adjust, double, double) -> QPoint {
    GlyphVis& curr = glyphs[glyphName];

    int height = 0;
    int width = 0;


    width = width + adjust.x();
    height = height + adjust.y();

    return QPoint(width, height);
  };

  MarkBaseSubtable* newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "defaultwaqfmarktobase";
  newsubtable->base = { "isol|fina|smallwaw|smallyeh" };


  newsubtable->classes["waqfmarks"].mark = { "waqfmarks" };
  newsubtable->classes["waqfmarks"].basefunction = basefunction;
  newsubtable->classes["waqfmarks"].markfunction = markfunction;

  return lookup;
}
Lookup* Automedina::defaultdotmarks() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultdotmarks";
  lookup->feature = "mark";
  lookup->type = Lookup::mark2base;
  lookup->flags = 0;


  MarkBaseSubtable* newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);

  /*classes["topdotmarks"] = {
                "onedotup",
                "twodotsup",
                "three_dots"
        };

        classes["downdotmarks"] = {
                "onedotdown",
                "twodotsdown"
        };*/

  newsubtable->name = "onedotup";
  newsubtable->base = { "^behshape|^hah|^fehshape|^dal|^reh|^sad|^tah|^ain" };
  newsubtable->classes["onedotup"].mark = { "onedotup" };
  newsubtable->classes["onedotup"].basefunction = Defaulbaseanchorfortopdots(*this, *newsubtable);
  newsubtable->classes["onedotup"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);
  newsubtable->name = "twodotsup";
  newsubtable->base = { "^behshape|^fehshape|^heh" };
  newsubtable->classes["twodotsup"].mark = { "twodotsup" };
  newsubtable->classes["twodotsup"].basefunction = Defaulbaseanchorfortopdots(*this, *newsubtable);
  newsubtable->classes["twodotsup"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);
  newsubtable->name = "three_dots";
  newsubtable->base = { "^behshape|^seen" };
  newsubtable->classes["three_dots"].mark = { "three_dots" };
  newsubtable->classes["three_dots"].basefunction = Defaulbaseanchorfortopdots(*this, *newsubtable);
  newsubtable->classes["three_dots"].markfunction = Defaultopmarkanchor(*this, *newsubtable);

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);
  newsubtable->name = "onedotdown";
  newsubtable->base = { "^behshape|^hah" };
  newsubtable->classes["onedotdown"].mark = { "onedotdown" };
  newsubtable->classes["onedotdown"].basefunction = Defaulbaseanchorforlowdots(*this, *newsubtable);
  newsubtable->classes["onedotdown"].markfunction = Defaullowmarkanchor(*this, *newsubtable);

  newsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(newsubtable);
  newsubtable->name = "twodotsdown";
  newsubtable->base = { "^behshape" };
  newsubtable->classes["twodotsdown"].mark = { "twodotsdown" };
  newsubtable->classes["twodotsdown"].basefunction = Defaulbaseanchorforlowdots(*this, *newsubtable);
  newsubtable->classes["twodotsdown"].markfunction = Defaullowmarkanchor(*this, *newsubtable);

  return lookup;

}
Lookup* Automedina::defaultmkmk() {

  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultmkmk";
  lookup->feature = "mkmk";
  lookup->type = Lookup::mark2mark;
  lookup->flags = 0;

  MarkBaseSubtable* subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "defaultmkmktop";
  subtable->base = { "hamzaabove","hamzaabove.joined","hamzaabove.lamalef", "shadda","smallalef","smallalef.joined","smallalef.replacement","smallhighseen", "smallhighwaw","smallhighyeh" };

  subtable->classes["topmarks"].mark = { "topmarks" };
  subtable->classes["topmarks"].basefunction = Defaultmarkabovemark(*this, *subtable);
  subtable->classes["topmarks"].markfunction = Defaultopmarkanchor(*this, *subtable);

  subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "defaultmkmkbottom";
  subtable->base = { "hamzabelow","hamzaabove.joined","smallhighyeh" };

  subtable->classes["lowmarks"].mark = { "lowmarks" };
  subtable->classes["lowmarks"].basefunction = Defaulbaseanchorforlow(*this, *subtable);
  subtable->classes["lowmarks"].markfunction = Defaullowmarkanchor(*this, *subtable);

  subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "defaultmkmkmeemiqlab";
  subtable->base = { "fatha","damma" };// "kasra"

  subtable->classes["meemiqlab"].mark = { "meemiqlab" };
  subtable->classes["meemiqlab"].basefunction = Defaultmarkabovemark(*this, *subtable);
  subtable->classes["meemiqlab"].markfunction = Defaultopmarkanchor(*this, *subtable);

  subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "smallhighseenwaqf.qaf";
  subtable->base = { "smallhighseen" };

  subtable->classes["waqf.qaf"].mark = { "waqf.qaf" };
  subtable->classes["waqf.qaf"].basefunction = Defaultmarkabovemark(*this, *subtable);
  subtable->classes["waqf.qaf"].markfunction = Defaultopmarkanchor(*this, *subtable);


  // hamzaabove.joined
  subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "hamzaabovejoined";
  subtable->base = { "maddahabove" };

  subtable->classes["hamzaabove.joined"].mark = { "hamzaabove.joined" };
  subtable->classes["hamzaabove.joined"].basefunction = nullptr; //;new Defaultmarkabovemark(*this, *smallhighseen);
  subtable->classes["hamzaabove.joined"].markfunction = nullptr; // new Defaultopmarkanchor(*this, *smallhighseen);


  m_layout->addLookup(lookup);

  // hamzaabove.joined

  lookup = new Lookup(m_layout);
  lookup->name = "smallalefjoined";
  lookup->feature = "mkmk";
  lookup->type = Lookup::mark2mark;
  lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef.joined"].charcode , (quint16)glyphs["hamzaabove.joined"].charcode });
  lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;

  subtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(subtable);

  subtable->name = "smallalefjoined";
  subtable->base = { "hamzaabove.joined" };

  subtable->classes["smallalef.joined"].mark = { "smallalef.joined" };
  //subtable->classes["smallalef.joined"].baseanchors = { { "smallalef.joined", 1 } }
  subtable->classes["smallalef.joined"].markanchors = { { "smallalef.joined", QPoint(200,0) } };

  return lookup;

}
Lookup* Automedina::defaultmarkdotmarks() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultmarkdotmarkstop";
  lookup->feature = "mkmk";
  lookup->type = Lookup::mark2mark;
  lookup->flags = 0;


  MarkBaseSubtable* topsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(topsubtable);

  topsubtable->name = "defaultmarkdotmarkstop";
  topsubtable->base = { "topdotmarks" };

  auto basetopfunction = [this, topsubtable](QString glyphName, QString className, QPoint adjust, double, double) -> QPoint {
    GlyphVis& curr = glyphs[glyphName];


    int width = curr.width * 0.5;
    int height = (int)curr.height + 80;



    width = width + adjust.x();
    height = height + adjust.y();

    return QPoint(width, height);
  };

  auto topmarks = classes["topmarks"];
  topmarks.remove("shadda");

  topsubtable->classes["topmarks"].mark = topmarks;
  topsubtable->classes["topmarks"].basefunction = basetopfunction;
  topsubtable->classes["topmarks"].markfunction = Defaultopmarkanchor(*this, *topsubtable);

  topsubtable->classes["shadda"].mark = { "shadda" };
  topsubtable->classes["shadda"].basefunction = basetopfunction;
  topsubtable->classes["shadda"].markfunction = Defaultopmarkanchor(*this, *topsubtable);

  m_layout->addLookup(lookup);

  lookup = new Lookup(m_layout);
  lookup->name = "defaultmarkdotmarksbottom";
  lookup->feature = "mkmk";
  lookup->type = Lookup::mark2mark;
  lookup->flags = 0;
  lookup->setGlyphSet({ "downdotmarks","lowmarks" });

  MarkBaseSubtable* bottomsubtable = new MarkBaseSubtable(lookup);
  lookup->subtables.append(bottomsubtable);

  bottomsubtable->name = "defaultmarkdotmarksbottom";
  bottomsubtable->base = { "downdotmarks" };

  auto basedownfunction = [this, bottomsubtable](QString glyphName, QString className, QPoint adjust, double, double) -> QPoint {
    GlyphVis& curr = glyphs[glyphName];

    int depth = -(int)curr.depth + 50;
    int width = curr.width * 0.5;


    width = width + adjust.x();
    depth = depth - adjust.y();

    return QPoint(width, -depth);
  };

  bottomsubtable->classes["lowmarks"].mark = { "lowmarks" };
  bottomsubtable->classes["lowmarks"].basefunction = basedownfunction;
  bottomsubtable->classes["lowmarks"].markfunction = Defaullowmarkanchor(*this, *bottomsubtable);


  return lookup;

}
Lookup* Automedina::defaultwaqfmarkabovemarkprecise() {
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "defaultwaqfmarkabovemarkprecise";
  lookup->feature = "mark";
  lookup->type = Lookup::chainingpos;
  lookup->flags = 0;

  QSet<quint16> waqfmarks = classtoUnicode("waqfmarks");
  QSet<quint16> bases = classtoUnicode("bases");

  for (auto topmark : classes["topmarks"]) {

    QString sublookupName = topmark;

    Lookup* sublookup = new Lookup(m_layout);
    sublookup->name = lookup->name + "." + sublookupName;
    sublookup->feature = "";
    sublookup->type = Lookup::mark2base;
    sublookup->flags = 0;

    m_layout->addLookup(sublookup);

    MarkBaseSubtable* marksubtable = new MarkBaseSubtable(sublookup);
    sublookup->subtables.append(marksubtable);

    marksubtable->name = sublookup->name;
    marksubtable->base = { "bases" };


    marksubtable->classes["waqfmarks"].mark = { "waqfmarks" };
    marksubtable->classes["waqfmarks"].basefunction = Defaulbaseanchorfortop(*this, *marksubtable);
    marksubtable->classes["waqfmarks"].markfunction = Defaultopmarkanchor(*this, *marksubtable);


    ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);



    newsubtable->name = "topmarks_" + topmark;

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.backtrack.append(bases);
    newsubtable->compiledRule.backtrack.append(QSet{ (quint16)glyphs[topmark].charcode });
    newsubtable->compiledRule.input.append(waqfmarks);

    newsubtable->compiledRule.lookupRecords.append({ 0,sublookupName });
  }



  return lookup;

}
Lookup* Automedina::lowmarkafterwawandreh() {

  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "lowmarkafterwawandreh";
  lookup->feature = "mkmk";
  lookup->type = Lookup::chainingpos;

  lookup->markGlyphSetIndex = m_layout->addMarkSet({ "kasra", "kasratan", "onedotdown", "twodotsdown", "kasratanidgham" });
  lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;

  for (QString finaisol : {"fina.afterbehshape", "fina.afterseen", "fina", "isol" }) {
    for (QString kastradot : { "1", "2", "beforehah" }) {

      Lookup* sublookup = new Lookup(m_layout);
      sublookup->name = lookup->name + "." + finaisol + kastradot;
      sublookup->feature = "";
      sublookup->markGlyphSetIndex = m_layout->addMarkSet({ "kasra", "kasratan", "onedotdown", "twodotsdown", "kasratanidgham" });
      sublookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;

      MarkBaseSubtable* marksubtable = new MarkBaseSubtable(sublookup);
      sublookup->subtables.append(marksubtable);

      marksubtable->name = sublookup->name;
      if (kastradot == "1") {
        sublookup->type = Lookup::mark2base;
        marksubtable->base = { "[.]init|[.]isol" };

        marksubtable->classes["lowmarks"].mark = { "kasra", "onedotdown", "twodotsdown" };
        marksubtable->classes["lowmarks"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
        marksubtable->classes["lowmarks"].markfunction = Defaullowmarkanchor(*this, *marksubtable);

        marksubtable->classes["kasratan"].mark = { "kasratan",  "kasratanidgham" };
        marksubtable->classes["kasratan"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
        marksubtable->classes["kasratan"].markfunction = Defaullowmarkanchor(*this, *marksubtable);

      }
      else if (kastradot == "2") {
        //sublookup->type = Lookup::mark2mark;
        //marksubtable->base = { "onedotdown", "twodotsdown" };

        sublookup->type = Lookup::mark2base;
        marksubtable->base = { "(behshape|hah)[.](init|isol)" };

        marksubtable->classes["kasra"].mark = { "kasra", };
        marksubtable->classes["kasra"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
        marksubtable->classes["kasra"].markfunction = Defaullowmarkanchor(*this, *marksubtable);

        marksubtable->classes["kasratan"].mark = { "kasratan", "kasratanidgham" };
        marksubtable->classes["kasratan"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
        marksubtable->classes["kasratan"].markfunction = Defaullowmarkanchor(*this, *marksubtable);


      }
      else if (kastradot == "beforehah") {
        sublookup->type = Lookup::mark2base;
        marksubtable->base = { "reh|waw" };

        marksubtable->classes["kasra"].mark = { "kasra" };
        marksubtable->classes["kasra"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
        marksubtable->classes["kasra"].markfunction = Defaullowmarkanchor(*this, *marksubtable);
      }

      m_layout->addLookup(sublookup);
    }
    // displac
    /*
                if (finaisol == "isol") {
                        Lookup * sublookup = new Lookup(m_layout);
                        sublookup->name = lookup->name + "." + finaisol + "displac";
                        sublookup->feature = "";
                        sublookup->is_gsub = false;
                        sublookup->local = true;
                        sublookup->type = Lookup::singleadjustment;

                        m_layout->addLookup(sublookup, true);

                        SingleAdjustmentSubtable* singleadjsubtable = new SingleAdjustmentSubtable(sublookup);
                        sublookup->subtables.append(singleadjsubtable);

                        singleadjsubtable->name = sublookup->name;

                        auto applied = classtoUnicode("(waw|reh)[.]" + finaisol);
                        for (auto glyph : applied) {
                                singleadjsubtable->singlePos[glyph] = { 0,0,0,0 };
                        }
                }*/

                /*
                            //rehwawcursive
                            Lookup * sublookup = new Lookup(m_layout);
                            sublookup->name = lookup->name + "." + finaisol + "rehwawcursive";
                            sublookup->feature = "";
                            sublookup->type = Lookup::cursive;
                            sublookup->is_gsub = false;
                            sublookup->local = true;
                            sublookup->flags = Lookup::Flags::IgnoreMarks;

                            m_layout->addLookup(sublookup, true);

                            CursiveSubtable* cursivesubtable = new CursiveSubtable(lookup);
                            sublookup->subtables.append(cursivesubtable);
                            cursivesubtable->name = "cursivesubtable";

                            auto& glyphcodes = m_layout->classtoUnicode("(waw|reh)[.]" + finaisol);

                            for (auto glyphcode : glyphcodes) {
                                    cursivesubtable->anchors[glyphcode].exit = QPoint(0, 0);
                            }

                            glyphcodes = m_layout->classtoUnicode("isol|init"); //"((?<!reh|waw)[.]isol)|init"

                            for (auto glyphcode : glyphcodes) {
                                    QString glyphName = m_layout->glyphNamePerCode[glyphcode];
                                    auto glyph = glyphs[glyphName];
                                    bool includeGlyph = true;
                                    for (auto anchors : exitAnchorsRTL) {
                                            if (anchors.contains(glyphcode)) {
                                                    includeGlyph = false;
                                                    break;
                                            }
                                    }

                                    if (includeGlyph) {
                                            cursivesubtable->anchors[glyphcode].entry = QPoint(glyph.width, 0);
                                    }

                            }*/

                            // beforehah
    ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->name = "chaining_" + finaisol;

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.input.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });
    newsubtable->compiledRule.input.append(classtoUnicode("hah[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["onedotdown"].charcode,(quint16)glyphs["twodotsdown"].charcode });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });

    //if (finaisol == "isol") {
    //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    //}
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "beforehah" });
    newsubtable->compiledRule.lookupRecords.append({ 3,lookup->name + "." + finaisol + "1" });
    newsubtable->compiledRule.lookupRecords.append({ 4,lookup->name + "." + finaisol + "2" });


    //
    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->name = "chaining_" + finaisol;

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.backtrack.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.backtrack.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });
    newsubtable->compiledRule.input.append(classtoUnicode("[.]init|[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["onedotdown"].charcode,(quint16)glyphs["twodotsdown"].charcode });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });

    if (finaisol == "isol") {
      //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "1" });
    newsubtable->compiledRule.lookupRecords.append({ 2,lookup->name + "." + finaisol + "2" });

    //
    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.backtrack.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.input.append(classtoUnicode("[.]init|[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["onedotdown"].charcode,(quint16)glyphs["twodotsdown"].charcode });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });

    if (finaisol == "isol") {
      //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "1" });
    newsubtable->compiledRule.lookupRecords.append({ 2,lookup->name + "." + finaisol + "2" });

    // beforehah
    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.input.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });
    newsubtable->compiledRule.input.append(classtoUnicode("hah[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode,(quint16)glyphs["onedotdown"].charcode ,(quint16)glyphs["twodotsdown"].charcode });

    if (finaisol == "isol") {
      //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "beforehah" });
    newsubtable->compiledRule.lookupRecords.append({ 3,lookup->name + "." + finaisol + "1" });

    //
    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();
    newsubtable->compiledRule.backtrack.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.backtrack.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });
    newsubtable->compiledRule.input.append(classtoUnicode("[.]init|[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode,(quint16)glyphs["onedotdown"].charcode ,(quint16)glyphs["twodotsdown"].charcode });

    if (finaisol == "isol") {
      //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "1" });

    //
    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();
    newsubtable->compiledRule.backtrack.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.input.append(classtoUnicode("[.]init|[.]isol"));
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode, (quint16)glyphs["onedotdown"].charcode ,(quint16)glyphs["twodotsdown"].charcode });

    if (finaisol == "isol") {
      //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "1" });

    newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();
    newsubtable->compiledRule.input.append({ classtoUnicode("(waw|reh)[.]" + finaisol) });
    newsubtable->compiledRule.input.append({ (quint16)glyphs["kasra"].charcode,(quint16)glyphs["kasratan"].charcode,(quint16)glyphs["kasratanidgham"].charcode });
    newsubtable->compiledRule.lookahead.append(classtoUnicode("hah[.]isol|ain[.]isol"));

    if (finaisol == "isol") {
      //	newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "displac" });
    }
    //newsubtable->compiledRule.lookupRecords.append({ 0,lookup->name + "." + finaisol + "rehwawcursive" });
    newsubtable->compiledRule.lookupRecords.append({ 1,lookup->name + "." + finaisol + "beforehah" });

  }
  //}

  return lookup;


}
Lookup* Automedina::tajweedcolorcpp() {

  Lookup* single = new Lookup(m_layout);
  single->name = "tajweedcolor.green";
  single->feature = "";
  single->type = Lookup::singleadjustment;
  m_layout->addLookup(single);

  ValueRecord green{ 99, 200, 77, 0 };
  ValueRecord gray{ 200, 200, 200, 0 };
  ValueRecord lkalkala{ 200, 200, 200, 0 };

  SingleAdjustmentSubtable* newsubtable = new SingleAdjustmentSubtable(single, 3);
  single->subtables.append(newsubtable);
  newsubtable->name = single->name;
  for (auto className : { "bases" ,"marks" }) {
    auto  unicodes = m_layout->classtoUnicode(className);
    for (auto unicode : unicodes) {

      newsubtable->singlePos[unicode] = green;
    }
  }

  single = new Lookup(m_layout);
  single->name = "tajweedcolor.lgray";
  single->feature = "";
  single->type = Lookup::singleadjustment;
  m_layout->addLookup(single);

  newsubtable = new SingleAdjustmentSubtable(single, 3);
  single->subtables.append(newsubtable);
  newsubtable->name = single->name;
  for (auto className : { "^meem|^behshape|onedotup|^noon" ,"marks" }) {
    auto  unicodes = m_layout->classtoUnicode(className);
    for (auto unicode : unicodes) {

      newsubtable->singlePos[unicode] = gray;
    }
  }

  single = new Lookup(m_layout);
  single->name = "tajweedcolor.lkalkala";
  single->feature = "";
  single->type = Lookup::singleadjustment;
  m_layout->addLookup(single);

  newsubtable = new SingleAdjustmentSubtable(single, 3);
  single->subtables.append(newsubtable);
  newsubtable->name = single->name;
  for (auto className : { "^tah|^behshape|^dal|^hah|^kaf|^fehshape" ,"marks" }) {
    auto  unicodes = m_layout->classtoUnicode(className);
    for (auto unicode : unicodes) {
      newsubtable->singlePos[unicode] = lkalkala;
    }
  }


  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "tajweedcolor";
  lookup->feature = "mkmk";
  lookup->type = Lookup::chainingpos;
  lookup->flags = 0;

  //tajweedcolor_meemiqlab1
  ChainingSubtable* chainingsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(chainingsubtable);

  chainingsubtable->name = "tajweedcolor_meemiqlab1";

  chainingsubtable->compiledRule = ChainingSubtable::CompiledRule();

  chainingsubtable->compiledRule.input.append(classtoUnicode("^noon"));
  chainingsubtable->compiledRule.input.append(classtoUnicode("meemiqlab"));

  chainingsubtable->compiledRule.lookupRecords.append({ 0,"lgray" });
  chainingsubtable->compiledRule.lookupRecords.append({ 1,"green" });

  //tajweedcolor_meemiqlab2
  chainingsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(chainingsubtable);

  chainingsubtable->name = "tajweedcolor_meemiqlab2";

  chainingsubtable->compiledRule = ChainingSubtable::CompiledRule();

  chainingsubtable->compiledRule.input.append(classtoUnicode("^behshape"));
  chainingsubtable->compiledRule.input.append(classtoUnicode("onedotup"));
  chainingsubtable->compiledRule.input.append(classtoUnicode("meemiqlab"));

  chainingsubtable->compiledRule.lookupRecords.append({ 0,"lgray" });
  chainingsubtable->compiledRule.lookupRecords.append({ 1,"lgray" });
  chainingsubtable->compiledRule.lookupRecords.append({ 2,"green" });

  //tajweedcolor_meemnoon
  chainingsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(chainingsubtable);

  chainingsubtable->name = "tajweedcolor_meemnoon";

  chainingsubtable->compiledRule = ChainingSubtable::CompiledRule();

  chainingsubtable->compiledRule.input.append(classtoUnicode("^meem|^noon"));
  chainingsubtable->compiledRule.input.append(classtoUnicode("shadda"));
  chainingsubtable->compiledRule.input.append(classtoUnicode("marks"));

  chainingsubtable->compiledRule.lookupRecords.append({ 0,"green" });
  chainingsubtable->compiledRule.lookupRecords.append({ 1,"green" });
  chainingsubtable->compiledRule.lookupRecords.append({ 2,"green" });


  return lookup;


}
Lookup* Automedina::pointmarks() {

  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "pointmarks";
  lookup->feature = "mark";
  lookup->type = Lookup::chainingpos;
  lookup->flags = 0;
  //lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode });
  //lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;

  for (auto pointmark : classes["dotmarks"]) {

    QString sublookupName = pointmark;

    Lookup* sublookup = new Lookup(m_layout);
    sublookup->name = lookup->name + "." + sublookupName;
    sublookup->feature = "";
    sublookup->type = Lookup::mark2base;
    sublookup->flags = 0;

    m_layout->addLookup(sublookup);

    MarkBaseSubtable* marksubtable = new MarkBaseSubtable(sublookup);
    sublookup->subtables.append(marksubtable);

    marksubtable->name = sublookup->name;
    marksubtable->base = { "bases" };

    marksubtable->classes["topmarks"].mark = { "topmarks" };
    marksubtable->classes["topmarks"].basefunction = Defaulbaseanchorfortop(*this, *marksubtable);
    marksubtable->classes["topmarks"].markfunction = Defaultopmarkanchor(*this, *marksubtable);


    marksubtable->classes["lowmarks"].mark = { "lowmarks" };
    marksubtable->classes["lowmarks"].basefunction = Defaulbaseanchorforlow(*this, *marksubtable);
    marksubtable->classes["lowmarks"].markfunction = Defaullowmarkanchor(*this, *marksubtable);


    ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
    lookup->subtables.append(newsubtable);



    newsubtable->name = "pointmarks_" + pointmark;

    newsubtable->compiledRule = ChainingSubtable::CompiledRule();

    newsubtable->compiledRule.backtrack.append({ classtoUnicode("bases") });
    newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs[pointmark].charcode });
    newsubtable->compiledRule.input.append(classtoUnicode("marks"));

    newsubtable->compiledRule.lookupRecords.append({ 1,sublookupName });
  }



  return lookup;


}

Lookup* Automedina::ayanumberskern() {

  if (extended) {
    return nullptr;
  }

  auto& ayaGlyph = glyphs["endofaya"];
  auto digitySet = classtoUnicode("digits");
  qint16 yoffset = 150;

  // three digits
  Lookup* sublookup = new Lookup(m_layout);
  sublookup->name = "ayanumberskern.l1";
  sublookup->feature = "";
  sublookup->type = Lookup::singleadjustment;
  m_layout->addLookup(sublookup);

  SingleAdjustmentSubtable* singleadjsubtable = new SingleAdjustmentSubtable(sublookup);
  sublookup->subtables.append(singleadjsubtable);

  singleadjsubtable->name = sublookup->name;

  for (auto digit : digitySet) {
    singleadjsubtable->singlePos[digit] = { 0,yoffset,-700,0 };
  }

  // two digits
  sublookup = new Lookup(m_layout);
  sublookup->name = "ayanumberskern.l2";
  sublookup->feature = "";
  sublookup->type = Lookup::singleadjustment;
  m_layout->addLookup(sublookup);

  singleadjsubtable = new SingleAdjustmentSubtable(sublookup);
  sublookup->subtables.append(singleadjsubtable);

  singleadjsubtable->name = sublookup->name;

  for (auto digit : digitySet) {
    singleadjsubtable->singlePos[digit] = { 0,yoffset,-500,0 };
  }

  // 1 digit
  sublookup = new Lookup(m_layout);
  sublookup->name = "ayanumberskern.l3";
  sublookup->feature = "";
  sublookup->type = Lookup::singleadjustment;
  m_layout->addLookup(sublookup);

  singleadjsubtable = new SingleAdjustmentSubtable(sublookup);
  sublookup->subtables.append(singleadjsubtable);

  singleadjsubtable->name = sublookup->name;

  for (auto digit : digitySet) {
    singleadjsubtable->singlePos[digit] = { 0,yoffset,-300,0 };
  }

  // up
  sublookup = new Lookup(m_layout);
  sublookup->name = "ayanumberskern.up";
  sublookup->feature = "";
  sublookup->type = Lookup::singleadjustment;
  m_layout->addLookup(sublookup);

  singleadjsubtable = new SingleAdjustmentSubtable(sublookup);
  sublookup->subtables.append(singleadjsubtable);

  singleadjsubtable->name = sublookup->name;

  for (auto digit : digitySet) {
    singleadjsubtable->singlePos[digit] = { 0,yoffset,0,0 };
  }





  //main lokkup



  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "ayanumberskern";
  lookup->feature = "kern";
  lookup->type = Lookup::chainingpos;
  lookup->flags = 0;
  //lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode });
  //lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;




  ChainingSubtable* subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers3digits";
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  //subtable->compiledRule.backtrack = {{(int16_t)ayaGlyph.charcode}};
  subtable->compiledRule.input = { {(uint16_t)ayaGlyph.charcode}, digitySet,digitySet,digitySet };
  subtable->compiledRule.lookupRecords.append({ 1,"l1" });
  subtable->compiledRule.lookupRecords.append({ 2,"up" });
  subtable->compiledRule.lookupRecords.append({ 3,"up" });

  subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers2digits";
  //subtable->compiledRule.backtrack = {{(int16_t)ayaGlyph.charcode}};
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  subtable->compiledRule.input = { {(uint16_t)ayaGlyph.charcode}, digitySet,digitySet };
  subtable->compiledRule.lookupRecords.append({ 1,"l2" });
  subtable->compiledRule.lookupRecords.append({ 2,"up" });

  subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers1digit";
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  subtable->compiledRule.input = { {(uint16_t)ayaGlyph.charcode}, digitySet };
  subtable->compiledRule.lookupRecords.append({ 1,"l3" });

  return lookup;


}

Lookup* Automedina::ayanumbers() {

  quint16 endofaya = m_layout->glyphCodePerName["endofaya"];

  // ligature
  Lookup* ligature = new Lookup(m_layout);
  ligature->name = "ayanumbers.l1";
  ligature->feature = "";
  ligature->type = Lookup::ligature;
  m_layout->addLookup(ligature);

  LigatureSubtable* ligaturesubtable = new LigatureSubtable(ligature);
  ligature->subtables.append(ligaturesubtable);
  ligaturesubtable->name = ligature->name;

  for (quint16 i = 286; i > 99; i--) {
    quint16 code = m_layout->glyphCodePerName[QString("aya%1").arg(i)];

    int onesdigit = i % 10;
    int tensdigit = (i / 10) % 10;
    int hundredsdigit = i / 100;
    if (extended) {
      ligaturesubtable->ligatures.append({ code, { (quint16)(m_layout->unicodeToGlyphCode.value(1632 + hundredsdigit)),
                                                   (quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),
                                                   (quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)) } });
    }
    else {
      ligaturesubtable->ligatures.append({ code, { (quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)),
                                                   (quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),
                                                   (quint16)(m_layout->unicodeToGlyphCode.value(1632 + hundredsdigit)),endofaya } });
      ligaturesubtable->ligatures.append({ code, {endofaya,(quint16)(m_layout->unicodeToGlyphCode.value(1632 + hundredsdigit)),
                                                  (quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),
                                                  (quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)) } });
    }


  }

  // ligature
  ligature = new Lookup(m_layout);
  ligature->name = "ayanumbers.l2";
  ligature->feature = "";
  ligature->type = Lookup::ligature;
  m_layout->addLookup(ligature);

  ligaturesubtable = new LigatureSubtable(ligature);
  ligature->subtables.append(ligaturesubtable);
  ligaturesubtable->name = ligature->name;

  for (quint16 i = 99; i > 9; i--) {
    quint16 code = m_layout->glyphCodePerName[QString("aya%1").arg(i)];
    int onesdigit = i % 10;
    int tensdigit = i / 10;
    if (extended) {
      ligaturesubtable->ligatures.append({ code,{ (quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),
                                                  (quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)) } });
    }
    else {
      ligaturesubtable->ligatures.append({ code,{(quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)),
                                                  (quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),endofaya } });
      ligaturesubtable->ligatures.append({ code,{endofaya,(quint16)(m_layout->unicodeToGlyphCode.value(1632 + tensdigit)),
                                                 (quint16)(m_layout->unicodeToGlyphCode.value(1632 + onesdigit)) } });
    }

  }
  if (extended) {
    // Single substitution
    Lookup* single = new Lookup(m_layout);
    single->name = "ayanumbers.l3";
    single->feature = "";
    single->type = Lookup::single;
    m_layout->addLookup(single);

    SingleSubtable* singlesubtable = new SingleSubtable(single);
    single->subtables.append(singlesubtable);
    singlesubtable->name = single->name;

    for (int i = 1; i < 10; i++) {
      singlesubtable->subst[(quint16)(m_layout->unicodeToGlyphCode.value(1632 + i))] = glyphs[QString("aya%1").arg(i)].charcode;
    }

  }
  else {

    // ligature
    ligature = new Lookup(m_layout);
    ligature->name = "ayanumbers.l3";
    ligature->feature = "";
    ligature->type = Lookup::ligature;
    m_layout->addLookup(ligature);

    ligaturesubtable = new LigatureSubtable(ligature);
    ligature->subtables.append(ligaturesubtable);
    ligaturesubtable->name = ligature->name;

    for (int i = 1; i < 10; i++) {
      quint16 code = m_layout->glyphCodePerName[QString("aya%1").arg(i)];
      ligaturesubtable->ligatures.append({ code,{endofaya,(quint16)(m_layout->unicodeToGlyphCode.value(1632 + i))} });
      ligaturesubtable->ligatures.append({ code,{(quint16)(m_layout->unicodeToGlyphCode.value(1632 + i)),endofaya} });
    }

  }


  //main lokkup



  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "ayanumbers";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->flags = 0;
  //lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode });
  //lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;

  auto digitySet = classtoUnicode("digits");

  auto digitySetplusendofaya = digitySet;
  digitySetplusendofaya.insert(endofaya);


  ChainingSubtable* subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers3digits";
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  if (extended) {
    subtable->compiledRule.input = { digitySet,digitySet,digitySet };
  }
  else {
    //subtable->compiledRule.input = {digitySet,digitySet,digitySet,{endofaya} };
    subtable->compiledRule.input = { digitySetplusendofaya,digitySet,digitySet,digitySetplusendofaya };
  }

  subtable->compiledRule.lookupRecords.append({ 0,"l1" });

  subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers2digits";
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  if (extended) {
    subtable->compiledRule.input = { digitySet,digitySet };
  }
  else {
    subtable->compiledRule.input = { digitySetplusendofaya,digitySet,digitySetplusendofaya };
  }
  subtable->compiledRule.lookupRecords.append({ 0,"l2" });

  subtable = new ChainingSubtable(lookup);
  lookup->subtables.append(subtable);
  subtable->name = "ayanumbers1digit";
  subtable->compiledRule = ChainingSubtable::CompiledRule();
  if (extended) {
    subtable->compiledRule.input = { digitySet };
  }
  else {

    subtable->compiledRule.input = { digitySetplusendofaya,digitySetplusendofaya };
  }
  subtable->compiledRule.lookupRecords.append({ 0,"l3" });

  return lookup;

}
Lookup* Automedina::forheh() {

  Lookup* single = new Lookup(m_layout);
  single->name = "forheh.l1";
  single->feature = "";
  single->type = Lookup::single;
  m_layout->addLookup(single);

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;


  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + 2) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + 2) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }


  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "forheh";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->flags = 0;
  //lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode });
  lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;

  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forheh";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }


  //newsubtable->compiledRule.input.append({ (quint16)glyphs["heh.medi"].charcode,(quint16)glyphs["heh.medi.forsmalllalef"].charcode });
  newsubtable->compiledRule.lookahead.append(classtoUnicode("^heh.medi")); //  { (quint16)glyphs["heh.medi"].charcode });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });

  return lookup;

}
Lookup* Automedina::forhamza() {

  Lookup* single = new Lookup(m_layout);
  single->name = "forhamza.l1";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  int tatweel = 2;

  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }

  // ligature
  Lookup* ligature = new Lookup(m_layout);
  ligature->name = "forhamza.l2";
  ligature->feature = "";
  ligature->type = Lookup::ligature;
  //ligature->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["hamzaabove"].charcode,(quint16)glyphs["smallhighyeh"].charcode,(quint16)glyphs["smallhighwaw"].charcode ,(quint16)glyphs["smallhighnoon"].charcode });
  //ligature->flags = ligature->flags | Lookup::Flags::UseMarkFilteringSet;
  m_layout->addLookup(ligature);

  LigatureSubtable* ligaturesubtable = new LigatureSubtable(ligature);
  ligature->subtables.append(ligaturesubtable);
  ligaturesubtable->name = ligature->name;

  ligaturesubtable->ligatures.append({ (quint16)glyphs["hamzaabove"].charcode,{ (quint16)glyphs["hamzaabove"].charcode  , 0x200D } });
  ligaturesubtable->ligatures.append({ (quint16)glyphs["hamzaabove.joined"].charcode,{ 0x200D,(quint16)glyphs["hamzaabove"].charcode } });
  ligaturesubtable->ligatures.append({ (quint16)glyphs["hamzaabove.joined"].charcode,{ (quint16)glyphs["tatweel"].charcode,(quint16)glyphs["hamzaabove"].charcode } });
  ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighyeh"].charcode,{ 0x200D,(quint16)glyphs["smallhighyeh"].charcode } });
  ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighyeh"].charcode,{ (quint16)glyphs["tatweel"].charcode,(quint16)glyphs["smallhighyeh"].charcode } });
  //ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighwaw"].charcode,{ 0x200D,(quint16)glyphs["smallhighwaw"].charcode } });
  //ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighwaw"].charcode,{ (quint16)glyphs["tatweel"].charcode,(quint16)glyphs["smallhighwaw"].charcode } });

  ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighnoon"].charcode,{ 0x200D,(quint16)glyphs["smallhighnoon"].charcode } });
  ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighnoon"].charcode,{ (quint16)glyphs["tatweel"].charcode,(quint16)glyphs["smallhighnoon"].charcode } });


  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "forhamza";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->markGlyphSetIndex = m_layout->addMarkSet({
    //(quint16)glyphs["smallhighwaw"].charcode,
    (quint16)glyphs["hamzaabove"].charcode,
    (quint16)glyphs["smallhighyeh"].charcode,
    (quint16)glyphs["smallhighnoon"].charcode,
    (quint16)glyphs["roundedfilledhigh"].charcode
    });
  lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;
  //lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;

  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forhamza";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }


  newsubtable->compiledRule.input.append({ 0x200D ,  (quint16)glyphs["tatweel"].charcode });
  newsubtable->compiledRule.input.append({ (quint16)glyphs["hamzaabove"].charcode,(quint16)glyphs["smallhighyeh"].charcode, (quint16)glyphs["smallhighnoon"].charcode });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });
  newsubtable->compiledRule.lookupRecords.append({ 1,"l2" });


  //roundedfilledhigh
  newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "roundedfilledhigh";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["roundedfilledhigh"].charcode, });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });


  return lookup;

}
Lookup* Automedina::shrinkstretchlt() {



  Lookup* lookup;
  int count = 1;
  for (float i = -0.1; i >= -0.7; i = i - 0.1) {
    lookup = shrinkstretchlt(i, QString("shr%1").arg(count));
    m_layout->addLookup(lookup);
    count++;
  }

  return nullptr;

}
Lookup* Automedina::shrinkstretchlt(float lt, QString featureName) {



  //m_layout->addLookup(forwaw(), false);

  QString lookupName;

  if (lt < 0) {
    lookupName = QString("minuslt_%1").arg(lt * -100);
  }
  else {
    lookupName = QString("pluslt_%1").arg(lt * -100);
  }

  Lookup* single = new Lookup(m_layout);
  single->name = lookupName + ".l1";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  for (auto& glyph : glyphs) {
    //QRegularExpression reg2("beginchar\\((.*?),(.*?),(.*?),(.*?)\\);");
    QRegularExpression regname("(.*)[.](minuslt|pluslt)_(.*)");
    QRegularExpressionMatch match = regname.match(glyph.name);
    if (match.hasMatch()) {
      QString name = match.captured(1);
      QString plusminus = match.captured(2);
      int value = match.captured(3).toInt();
    }
    else if (classes["haslefttatweel"].contains(glyph.name)) {
      if (lt < 0) {
        QString destName = QStringLiteral("%1.minuslt_%2").arg(glyph.name).arg((int)(lt * -100));
        if (glyphs.contains(destName)) {
          singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
        }
      }
      else {
        QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)(lt * 100));
        if (glyphs.contains(destName)) {
          singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
        }
      }

    }
    /*
                if (match.hasMatch()) {
                        int w1 = match.captured(1).toInt();
                        double w2 = match.captured(2).toDouble();

                if (classes["haslefttatweel"].contains(glyph.name)) {
                        QString destName = QStringLiteral("%1.minuslt_%2").arg(glyph.name).arg((int)(lt * 100));
                        if (glyphs.contains(destName)) {
                                singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
                        }
                }
                else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
                        QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt - shrink) * 100));
                        if (glyphs.contains(destName)) {
                                singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
                        }
                }*/
  }


  Lookup* lookup = new Lookup(m_layout);
  lookup->name = lookupName;
  lookup->feature = featureName;
  lookup->type = Lookup::chainingsub;
  lookup->flags = 0;


  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = lookupName;

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });

  return lookup;

}
Lookup* Automedina::forsmallhighwaw() {

  Lookup* single = new Lookup(m_layout);
  single->name = "forsmallhighwaw.l1";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  float tatweel = 1;

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }

  // ligature
  Lookup* ligature = new Lookup(m_layout);
  ligature->name = "forsmallhighwaw.l2";
  ligature->feature = "";
  ligature->type = Lookup::ligature;
  m_layout->addLookup(ligature);

  LigatureSubtable* ligaturesubtable = new LigatureSubtable(ligature);
  ligature->subtables.append(ligaturesubtable);
  ligaturesubtable->name = ligature->name;

  ligaturesubtable->ligatures.append({ (quint16)glyphs["smallhighwaw"].charcode,{ 0x034F,(quint16)glyphs["smallhighwaw"].charcode } });

  //main lookup
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "forsmallhighwaw";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->markGlyphSetIndex = m_layout->addMarkSet(QList{ (quint16)glyphs["smallhighwaw"].charcode });
  lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;



  //forsmallalefwithmaddah
  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "subtable1";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }
  newsubtable->compiledRule.input.append(QSet{ (quint16)0x034F });
  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["smallhighwaw"].charcode });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });
  newsubtable->compiledRule.lookupRecords.append({ 1,"l2" });



  return lookup;

}
Lookup* Automedina::forsmalllalef() {

  Lookup* single = new Lookup(m_layout);
  single->name = "forsmallalef.l1";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  float tatweel = 1;

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }

  singlesubtable->subst[glyphs["smallalef"].charcode] = glyphs["smallalef.joined"].charcode;

  //followed by maddahabove
  single = new Lookup(m_layout);
  single->name = "forsmallalef.l2";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  tatweel = 2;

  singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }

  //main lookup
  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "forsmallalef";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->flags = 0;
  lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode , (quint16)glyphs["maddahabove"].charcode });
  lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;



  //forsmallalefwithmaddah
  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forsmallalefwithmaddah";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["smallalef"].charcode });
  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["maddahabove"].charcode });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l2" });
  newsubtable->compiledRule.lookupRecords.append({ 1,"l1" });

  //forsmallalef
  newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forsmallalef";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["smallalef"].charcode });


  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });
  newsubtable->compiledRule.lookupRecords.append({ 1,"l1" });

  //forsmallalef
  newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forsmallalef";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["maddahabove"].charcode });
  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["smallalef"].charcode });


  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });
  newsubtable->compiledRule.lookupRecords.append({ 2,"l1" });



  return lookup;

}
QSet<quint16> Automedina::regexptoUnicode(QString regexp) {

  QSet<quint16> unicodes;

  QRegularExpression re(regexp);
  for (auto& glyph : m_layout->glyphs) {
    if (re.match(glyph.name).hasMatch()) {
      unicodes.insert(glyph.charcode);
    }
  }

  return unicodes;
}
QSet<quint16> Automedina::classtoUnicode(QString className) {



  if (cachedClasstoUnicode.contains(className)) {
    return cachedClasstoUnicode[className];
  }

  QSet<quint16> unicodes;

  if (!classes.contains(className)) {
    if (m_layout->glyphs.contains(className)) {
      auto& glyph = m_layout->glyphs[className];
      unicodes.insert(glyph.charcode);
    }
    else {
      bool ok;
      quint16 uniode = className.toUInt(&ok, 16);
      if (!ok) {
        QRegularExpression re(className);
        for (auto& glyph : m_layout->glyphs) {
          if (re.match(glyph.name).hasMatch()) {
            unicodes.insert(glyph.charcode);
          }
        }
      }
      else {
        unicodes.insert(uniode);
      }

    }
  }
  else {

    for (auto name : classes[className]) {
      unicodes.unite(classtoUnicode(name));
    }
  }

  cachedClasstoUnicode[className] = unicodes;
  return unicodes;
}

Lookup* Automedina::forwaw() {

  Lookup* single = new Lookup(m_layout);
  single->name = "forwaw.l1";
  single->feature = "";
  single->type = Lookup::single;

  m_layout->addLookup(single);

  SingleSubtable* singlesubtable = new SingleSubtable(single);
  single->subtables.append(singlesubtable);
  singlesubtable->name = single->name;

  float tatweel = 1;

  for (auto& glyph : glyphs) {
    if (classes["haslefttatweel"].contains(glyph.name)) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.name).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
    else if (classes["haslefttatweel"].contains(glyph.originalglyph) && glyph.name.contains("pluslt")) {
      QString destName = QStringLiteral("%1.pluslt_%2").arg(glyph.originalglyph).arg((int)((glyph.charlt + tatweel) * 100));
      if (glyphs.contains(destName)) {
        singlesubtable->subst[glyphs[glyph.name].charcode] = glyphs[destName].charcode;
      }
    }
  }


  Lookup* lookup = new Lookup(m_layout);
  lookup->name = "forwaw";
  lookup->feature = "rlig";
  lookup->type = Lookup::chainingsub;
  lookup->flags = 0;
  //lookup->markGlyphSetIndex = m_layout->addMarkSet({ (quint16)glyphs["smallalef"].charcode });
  //lookup->flags = lookup->flags | Lookup::Flags::UseMarkFilteringSet;
  lookup->flags = lookup->flags | Lookup::Flags::IgnoreMarks;

  ChainingSubtable* newsubtable = new ChainingSubtable(lookup);
  lookup->subtables.append(newsubtable);

  newsubtable->name = "forwaw";

  newsubtable->compiledRule = ChainingSubtable::CompiledRule();

  //newsubtable->compiledRule.input.append(singlesubtable->subst.keys().toSet());
  auto keys = singlesubtable->subst.keys();
  if (!keys.isEmpty()) {
    newsubtable->compiledRule.input.append(QSet(keys.begin(), keys.end()));
  }

  newsubtable->compiledRule.input.append(QSet{ (quint16)glyphs["waw.fina"].charcode });

  newsubtable->compiledRule.lookupRecords.append({ 0,"l1" });

  return lookup;
}

QSet<QString> Automedina::classtoGlyphName(QString className) {

  QSet<QString> names;
  //TODO use classtoUnicode
  if (!classes.contains(className)) {
    if (m_layout->glyphs.contains(className)) {
      auto& glyph = m_layout->glyphs[className];
      names.insert(glyph.name);
    }
    else {
      QRegularExpression re(className);
      for (auto& glyph : m_layout->glyphs) {
        if (re.match(glyph.name).hasMatch()) {
          names.insert(glyph.name);
        }
      }
    }
  }
  else {

    for (auto name : classes[className]) {
      names.unite(classtoGlyphName(name));
    }
  }

  return names;

}
void Automedina::addchars() {

  /*
        for (auto key : classes["haslefttatweel"]) {
                QString name = QStringLiteral("%1.beforeheh").arg(key);
                addchar(key, -1, 200 / 100.0, {}, {}, {}, {}, {}, name, 2);
        }*/
        /*
              for (auto key : classes["haslefttatweel"]) {
                      for (float i = 100; i <= 500; i = i + 100) {
                              QString name = QStringLiteral("%1.pluslt_%2").arg(key).arg((int)(i * 1));
                              addchar(key, -1, i / 100.0, {}, {}, {}, {}, {}, name, 2);
                      }


                      // for (float i = 10; i <= 200; i = i + 10) {
                      //	QString name = QStringLiteral("%1.minuslt_%2").arg(key).arg((int)(i * 1));
                      //	addchar(key, -1, -i / 100.0, {}, {}, {}, {}, {}, name, 2);
                      //}

                      QString metapostcode = QString("vardef %1.pluslt_[]_(expr lt,rt) = %1_(lt,rt);enddef;").arg(key);

                      QByteArray commandBytes = metapostcode.toLatin1();

                      int status = mp_execute(mp, commandBytes.data(), commandBytes.size());
                      if (status == mp_error_message_issued || status == mp_fatal_error_stop) {
                              mp_run_data * results = mp_rundata(mp);
                              QString ret(results->term_out.data);
                              ret.trimmed();
                              mp_finish(mp);
                              throw "Could not initialize MetaPost library instance!\n" + ret;
                      }
              }*/

              //behshape.init.minuslt_110
              //addchar("lam.medi", -1, {}, -0.2, {}, {}, {}, {}, "lam.medi.afterhah", 2);
  addchar("behshape.init", -1, -110 / 100.0, {}, {}, {}, {}, {}, "behshape.init.minuslt_110", 2);



}
void Automedina::addchar(QString macroname,
  int charcode,
  double lefttatweel,
  double righttatweel,
  optional<double> leftextratio,
  optional<double> rightextratio,
  optional<double> left_tatweeltension,
  optional<double> right_tatweeltension,
  QString newname,
  optional<int> which_in_baseline) {

  QString metapostcode = QString("beginchar(%1,%2,-1,-1,-1);").arg(newname).arg(charcode);

  if (leftextratio) {
    metapostcode = metapostcode + QString("interim left_verticalextratio := %1 ;").arg(*leftextratio);
  }
  if (rightextratio) {
    metapostcode = metapostcode + QString("interim right_verticalextratio := %1 ;").arg(*rightextratio);
  }
  if (left_tatweeltension) {
    metapostcode = metapostcode + QString("interim left_tatweeltension := %1 ;").arg(*left_tatweeltension);
  }
  if (right_tatweeltension) {
    metapostcode = metapostcode + QString("interim right_tatweeltension := %1 ;").arg(*right_tatweeltension);
  }
  if (which_in_baseline) {
    metapostcode = metapostcode + QString("interim which_in_baseline := %1 ;").arg(*which_in_baseline);
  }

  QString tst = QString("%1").arg(lefttatweel);
  QString tst2 = QString("%1").arg(righttatweel); // metapostcode + QString("%1").number(0.10764366596638640, 'g', 6);

  metapostcode = metapostcode + QString("%1_(%2,%3);endchar;").arg(macroname).arg(lefttatweel).arg(righttatweel);



  QByteArray commandBytes = metapostcode.toLatin1();

  int status = mp_execute(mp, commandBytes.data(), commandBytes.size());
  if (status == mp_error_message_issued || status == mp_fatal_error_stop) {
    mp_run_data* results = mp_rundata(mp);
    QString ret(results->term_out.data);
    ret.trimmed();
    qDebug() << "Metapost error" << ret;
    //mp_finish(mp);
    //throw "Could not initialize MetaPost library instance!\n" + ret;
  }




}


