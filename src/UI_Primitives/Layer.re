open Revery_UI;
open React;

let%nativeComponent make = 
                    (
                      ~condition: RenderCondition.t,
                      ~onMouseDown=?,
                      ~onMouseMove=?,
                      ~onMouseUp=?,
                      ~onMouseWheel=?,
                      ~onMouseEnter=?,
                      ~onMouseLeave=?,
                      ~onMouseOver=?,
                      ~onMouseOut=?,
                      ~style=Style.emptyViewStyle,
                      ~children=React.empty,
                      ~onDimensionsChanged=?,
                      ~onBoundingBoxChanged=?,
                      ~onFileDropped=?,
                      ~mouseBehavior=Revery_UI.Normal,
                      (),
                      hooks,
                    ) => (
  {
    make: () => {
      let styles = Style.create(~style, ());
      let events =
        NodeEvents.make(
          ~onMouseDown?,
          ~onMouseMove?,
          ~onMouseUp?,
          ~onMouseWheel?,
          ~onMouseEnter?,
          ~onMouseLeave?,
          ~onMouseOver?,
          ~onMouseOut?,
          ~onDimensionsChanged?,
          ~onBoundingBoxChanged?,
          ~onFileDropped?,
          (),
        );
      let node = PrimitiveNodeFactory.get().createLayerNode(condition);
      node#setEvents(events);
      node#setStyle(styles);
      node;
    },
    configureInstance: (~isFirstRender as _, node) => {
      let styles = Style.create(~style, ());
      let events =
        NodeEvents.make(
          ~onMouseDown?,
          ~onMouseMove?,
          ~onMouseUp?,
          ~onMouseWheel?,
          ~onMouseEnter?,
          ~onMouseLeave?,
          ~onMouseOver?,
          ~onMouseOut?,
          ~onBoundingBoxChanged?,
          ~onDimensionsChanged?,
          ~onFileDropped?,
          (),
        );
      node#setEvents(events);
      node#setStyle(styles);
      node#setMouseBehavior(mouseBehavior);
      node#setCondition(condition);
      node;
    },
    children,
    insertNode:{(~parent, ~child,~position) => {
    parent#addChild(child, position);
    parent;
    }},
    deleteNode:{(~parent, ~child, ~position) => {
    parent#removeChild(child);
    parent;
      }},
    moveNode:{(~parent, ~child, ~from, ~to_) => {
      parent
      }},
  },
  hooks,
);
