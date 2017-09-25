[%bs.raw {|require('./index.css')|}];

Utils.register_service_worker ();

let render route => ReactDOMRe.renderToElementWithId <App route /> "root";

let router =
  DirectorRe.makeRouter {
    "/": fun () => render Routes.Front,
    "/comments/:id": fun (id: string) => render (Routes.Comments (int_of_string id))
  };

DirectorRe.init router "/";
