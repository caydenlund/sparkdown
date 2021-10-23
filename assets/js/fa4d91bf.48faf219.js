"use strict";(self.webpackChunksparkdown_docs=self.webpackChunksparkdown_docs||[]).push([[930],{3905:function(e,t,n){n.d(t,{Zo:function(){return p},kt:function(){return m}});var r=n(7294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),c=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},p=function(e){var t=c(e.components);return r.createElement(s.Provider,{value:t},e.children)},d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},u=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),u=c(n),m=a,h=u["".concat(s,".").concat(m)]||u[m]||d[m]||o;return n?r.createElement(h,i(i({ref:t},p),{},{components:n})):r.createElement(h,i({ref:t},p))}));function m(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,i=new Array(o);i[0]=u;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l.mdxType="string"==typeof e?e:a,i[1]=l;for(var c=2;c<o;c++)i[c]=n[c];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}u.displayName="MDXCreateElement"},694:function(e,t,n){n.r(t),n.d(t,{frontMatter:function(){return l},contentTitle:function(){return s},metadata:function(){return c},toc:function(){return p},default:function(){return u}});var r=n(7462),a=n(3366),o=(n(7294),n(3905)),i=["components"],l={title:"Installation"},s=void 0,c={unversionedId:"installation",id:"installation",isDocsHomePage:!1,title:"Installation",description:"Install Bazel",source:"@site/docs/installation.mdx",sourceDirName:".",slug:"/installation",permalink:"/sparkdown/docs/installation",editUrl:"https://github.com/shrimpster00/sparkdown/edit/documentation/docs/installation.mdx",tags:[],version:"current",frontMatter:{title:"Installation"},sidebar:"docs",previous:{title:"Introduction",permalink:"/sparkdown/docs/intro"},next:{title:"Command Line Interface",permalink:"/sparkdown/docs/cli"}},p=[{value:"Install Bazel",id:"install-bazel",children:[],level:2},{value:"Download the most recent version of Sparkdown",id:"download-the-most-recent-version-of-sparkdown",children:[],level:2},{value:"Build Sparkdown",id:"build-sparkdown",children:[],level:2},{value:"Run the unit tests",id:"run-the-unit-tests",children:[],level:2}],d={toc:p};function u(e){var t=e.components,n=(0,a.Z)(e,i);return(0,o.kt)("wrapper",(0,r.Z)({},d,n,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h2",{id:"install-bazel"},"Install Bazel"),(0,o.kt)("p",null,"Sparkdown is built with ",(0,o.kt)("a",{parentName:"p",href:"https://bazel.build/"},"Bazel"),",\nthe open-source build tool developed by Google that simplifies\nthe process of scaffolding, scaling, building and testing large applications."),(0,o.kt)("p",null,"Follow the\n",(0,o.kt)("a",{parentName:"p",href:"https://docs.bazel.build/versions/main/install.html"},"installation instructions"),"\nto install Bazel. On Linux, you can install it from your package manager."),(0,o.kt)("p",null,"Bazel's documentation is quite thorough, and the installation instructions\nare not covered here."),(0,o.kt)("p",null,"Bazel will manage all other external dependencies relevant to Sparkdown;\nnothing else needs to be done."),(0,o.kt)("h2",{id:"download-the-most-recent-version-of-sparkdown"},"Download the most recent version of Sparkdown"),(0,o.kt)("p",null,"You can download the most recent release of Sparkdown from the\n",(0,o.kt)("a",{parentName:"p",href:"https://github.com/shrimpster00/sparkdown/releases"},"GitHub releases page"),"."),(0,o.kt)("p",null,"Alternatively, clone the repository\n",(0,o.kt)("a",{parentName:"p",href:"https://github.com/shrimpster00/sparkdown"},"from GitHub"),"\nand build the most recent commit."),(0,o.kt)("div",{className:"admonition admonition-caution alert alert--warning"},(0,o.kt)("div",{parentName:"div",className:"admonition-heading"},(0,o.kt)("h5",{parentName:"div"},(0,o.kt)("span",{parentName:"h5",className:"admonition-icon"},(0,o.kt)("svg",{parentName:"span",xmlns:"http://www.w3.org/2000/svg",width:"16",height:"16",viewBox:"0 0 16 16"},(0,o.kt)("path",{parentName:"svg",fillRule:"evenodd",d:"M8.893 1.5c-.183-.31-.52-.5-.887-.5s-.703.19-.886.5L.138 13.499a.98.98 0 0 0 0 1.001c.193.31.53.501.886.501h13.964c.367 0 .704-.19.877-.5a1.03 1.03 0 0 0 .01-1.002L8.893 1.5zm.133 11.497H6.987v-2.003h2.039v2.003zm0-3.004H6.987V5.987h2.039v4.006z"}))),"caution")),(0,o.kt)("div",{parentName:"div",className:"admonition-content"},(0,o.kt)("p",{parentName:"div"},"Sparkdown is still considered a work in progress; as such,\nbreaking changes are frequent and may occur at any time."),(0,o.kt)("p",{parentName:"div"},"Furthermore, the codebase does not build at this time\n(last updated 18 October, 2021)."))),(0,o.kt)("h2",{id:"build-sparkdown"},"Build Sparkdown"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"# First, cd into the `src` directory.\n[sparkdown-release-0.1.0] $ cd src/\n# Next, run the build command.\n[src] $ bazel build //sparkdown\n")),(0,o.kt)("p",null,"After that, Sparkdown has been built.\nThe relevant binaries are placed in the ",(0,o.kt)("inlineCode",{parentName:"p"},"src/bazel-bin/sparkdown")," directory."),(0,o.kt)("p",null,"At the time of writing (18 October, 2021), Sparkdown does not come with\nan install script. However, you can still add the binaries\nto your ",(0,o.kt)("inlineCode",{parentName:"p"},"PATH")," and use them from there.\nOn UNIX and UNIX-like systems,\nconvenient locations for binaries include ",(0,o.kt)("inlineCode",{parentName:"p"},"~/.local/bin/"),"\n(to install for the current user) and ",(0,o.kt)("inlineCode",{parentName:"p"},"/usr/local/bin/"),"\n(to install system-wide)."),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash",metastring:'title="Linux and UNIX systems"',title:'"Linux',and:!0,UNIX:!0,'systems"':!0},"# If we are installing for the user:\n[src] $ cp bazel-bin/sparkdown/sparkdown ~/.local/bin/\n# Alternatively, we can install system-wide:\n[src] $ sudo cp bazel-bin/sparkdown/sparkdown /usr/local/bin/\n")),(0,o.kt)("h2",{id:"run-the-unit-tests"},"Run the unit tests"),(0,o.kt)("p",null,"Sparkdown contains a host of unit tests that use the popular\n",(0,o.kt)("a",{parentName:"p",href:"https://google.github.io/googletest/"},"GoogleTest")," testing framework."),(0,o.kt)("p",null,"Bazel makes it very straightforward to run the unit tests; the command\nwill automatically fetch the GoogleTest library, compile\nthe necessary binaries, and run the tests."),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"# To run all tests,\n[src] $ bazel test //...\n# Alternatively, you can place further restrictions on the tests.\n[src] $ bazel test //lexer/...\n")),(0,o.kt)("p",null,"See the project's source on\n",(0,o.kt)("a",{parentName:"p",href:"https://github.com/shrimpster00/sparkdown/tree/main/src"},"GitHub"),"\nto get a feel for the project's structure."),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre"},"lexer\n|- lexers\n   |- abstract-lexer\n   |- arrow\n   |- bold\n   |- enumerate\n   |- header\n   |- italic\n   |- itemize\n   |- section\n   |- verbatim\n|- token\nsparkdown\nstate\n")))}u.isMDXComponent=!0}}]);