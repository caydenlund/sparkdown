"use strict";(self.webpackChunksparkdown_docs=self.webpackChunksparkdown_docs||[]).push([[713],{3905:function(e,t,n){n.d(t,{Zo:function(){return d},kt:function(){return m}});var r=n(7294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function l(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function i(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),p=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):l(l({},t),e)),n},d=function(e){var t=p(e.components);return r.createElement(s.Provider,{value:t},e.children)},c={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},u=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,d=i(e,["components","mdxType","originalType","parentName"]),u=p(n),m=a,f=u["".concat(s,".").concat(m)]||u[m]||c[m]||o;return n?r.createElement(f,l(l({ref:t},d),{},{components:n})):r.createElement(f,l({ref:t},d))}));function m(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,l=new Array(o);l[0]=u;var i={};for(var s in t)hasOwnProperty.call(t,s)&&(i[s]=t[s]);i.originalType=e,i.mdxType="string"==typeof e?e:a,l[1]=i;for(var p=2;p<o;p++)l[p]=n[p];return r.createElement.apply(null,l)}return r.createElement.apply(null,n)}u.displayName="MDXCreateElement"},4848:function(e,t,n){n.r(t),n.d(t,{frontMatter:function(){return i},contentTitle:function(){return s},metadata:function(){return p},toc:function(){return d},default:function(){return u}});var r=n(7462),a=n(3366),o=(n(7294),n(3905)),l=["components"],i={title:"Simple Example"},s=void 0,p={unversionedId:"getting-started/simple-example",id:"getting-started/simple-example",isDocsHomePage:!1,title:"Simple Example",description:"Create a Sparkdown file",source:"@site/docs/getting-started/simple-example.mdx",sourceDirName:"getting-started",slug:"/getting-started/simple-example",permalink:"/sparkdown/docs/getting-started/simple-example",editUrl:"https://github.com/shrimpster00/sparkdown/edit/documentation/docs/getting-started/simple-example.mdx",tags:[],version:"current",frontMatter:{title:"Simple Example"},sidebar:"getting-started",previous:{title:"Building Sparkdown",permalink:"/sparkdown/docs/getting-started/building"},next:{title:"Advanced Example",permalink:"/sparkdown/docs/getting-started/advanced-example"}},d=[{value:"Create a Sparkdown file",id:"create-a-sparkdown-file",children:[],level:2},{value:"Write the header of the document",id:"write-the-header-of-the-document",children:[],level:2},{value:"Write some markdown text",id:"write-some-markdown-text",children:[],level:2},{value:"Add some LaTeX text",id:"add-some-latex-text",children:[],level:2},{value:"Process the file",id:"process-the-file",children:[],level:2},{value:"Compile the PDF",id:"compile-the-pdf",children:[],level:2}],c={toc:d};function u(e){var t=e.components,i=(0,a.Z)(e,l);return(0,o.kt)("wrapper",(0,r.Z)({},c,i,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h2",{id:"create-a-sparkdown-file"},"Create a Sparkdown file"),(0,o.kt)("p",null,"Create a file; we'll use it as our notebook."),(0,o.kt)("p",null,"The name is not important, though it's customary to use the extension ",(0,o.kt)("inlineCode",{parentName:"p"},"_"),"."),(0,o.kt)("p",null,"For the purposes of this example, we'll refer to our file as ",(0,o.kt)("inlineCode",{parentName:"p"},"Notes._"),"."),(0,o.kt)("h2",{id:"write-the-header-of-the-document"},"Write the header of the document"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-markdown",metastring:'title="Notes._" {1-3}',title:'"Notes._"',"{1-3}":!0},"$author: Cayden Lund\n$title: Notes\n======\n")),(0,o.kt)("h2",{id:"write-some-markdown-text"},"Write some markdown text"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-markdown",metastring:'title="Notes._" {5-9}',title:'"Notes._"',"{5-9}":!0},"$author: Cayden Lund\n$title: Notes\n======\n\n*Italic text.*\n\n**Bold text.**\n\n# Section Heading\n")),(0,o.kt)("p",null,"This is enough for the Sparkdown compiler to recognize your intent and return valid LaTeX code."),(0,o.kt)("h2",{id:"add-some-latex-text"},"Add some LaTeX text"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-markdown",metastring:'title="Notes._" {9-11}',title:'"Notes._"',"{9-11}":!0},"$author: Cayden Lund\n$title: Notes\n======\n\n*Italic text.*\n\n**Bold text.**\n\n\\[\n    x = \\frac{-b \\pm \\sqrt{b^2-4ac}}{2a}\n\\]\n\n# Section Heading\n")),(0,o.kt)("p",null,"This is just an illustration that both languages are supported out-of-the-box."),(0,o.kt)("h2",{id:"process-the-file"},"Process the file"),(0,o.kt)("p",null,"We use our newly-built binary executable to parse the file:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"$ sparkdown Notes._ -o Notes.tex\n# The `-o` option tells the compiler the name of the file to create.\n")),(0,o.kt)("p",null,"We now have a new file, ",(0,o.kt)("inlineCode",{parentName:"p"},"Notes.tex"),", that is valid LaTeX code!"),(0,o.kt)("p",null,"If you want to read it, this is what it looks like:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-latex",metastring:'title="Notes.tex"',title:'"Notes.tex"'},"\\title{Notes}\n\\author{Cayden Lund}\n\\date{}\n\n\\documentclass[12pt, letterpaper]{article}\n\n\n\\usepackage{graphicx}\n\\graphicspath{{.}}\n\n\\usepackage[utf8]{inputenc}\n\n\\usepackage{tabularx}\n\n\\usepackage{amsmath}\n\n\n\\begin{document}\n\n\n\\maketitle\n\n\n\n\\textit{Italic text.}\n\n\\textbf{Bold text.}\n\n\\[\n    x = \\frac{-b \\pm \\sqrt{b^2-4ac}}{2a}\n\\]\n\n\n\\end{document}\n")),(0,o.kt)("h2",{id:"compile-the-pdf"},"Compile the PDF"),(0,o.kt)("p",null,"If you have ",(0,o.kt)("inlineCode",{parentName:"p"},"pdflatex")," installed, it's easy to compile the LaTeX into a PDF from there:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-bash"},"$ pdflatex Notes.tex\n# Compiles the file and creates Notes.pdf.\n")),(0,o.kt)("p",null,"Rendered output:"),(0,o.kt)("p",null,(0,o.kt)("img",{alt:"Rendered output",src:n(3700).Z})),(0,o.kt)("p",null,"This does of course rely on a LaTeX installation. Follow the ",(0,o.kt)("a",{parentName:"p",href:"https://www.latex-project.org/get/"},"LaTeX installation instructions"),"\nto get LaTeX and its necessary dependencies."))}u.isMDXComponent=!0},3700:function(e,t,n){t.Z=n.p+"assets/images/simple-example-output-a9e16953f8eeb767bf7c58d30499ed24.png"}}]);