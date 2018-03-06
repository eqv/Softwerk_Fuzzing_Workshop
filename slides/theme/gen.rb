require 'rexml/document'
require 'digest'
include REXML

$anims = []

$repl_bright = {
  "#fbf3f1" => "#35455d", #white to dark blue
  "#fc0a49" => "#647fa5", #main pink to bright blue
  "#eccf80" => "#35455d", #code yellow to dark blue
  "#fc0a48" => "#d00037", #hl pink to dark pink
  "#5692d7" => "#647fa5", #hl blue to bright blue
  "#34cd46" => "#008a0f", #hl green to dark green
  "#322a2a" => "#F8F9FB", #bakcground to background
  #"#eccf80" => "#f89f00", #yellow to orange
  #"#eccf80" => "#35455d", #yellow to dark blue
}

$repl_dark = {
}

$path_to_hashes = "../imgs/generated/hashes.msh"

class Generator

  attr_accessor :name, :outname, :last_md5sum

  def initialize(name,outname)
    @name = name
    @outname = outname
    puts "Created new obligation #{@name.inspect}"
    prev_hashes = File.read($path_to_hashes) rescue nil
    @last_md5sum = Marshal.load(prev_hashes)[@name+"|"+@outname] if prev_hashes
  end

  def get_md5sum()
    Digest::MD5.hexdigest(@name+"|"+@outname+"|"+File.read(@name))
  end

  def render
    return if @last_md5sum == get_md5sum
    generate
  end

end

class SvgAnim < Generator

  def generate
    xmlfile = File.new(@name)
    dom = Document.new(xmlfile)
    get_layers(dom).each do |layer|
      if layer !~ /\A__/
        generate_frame(dom,layer)
      end
    end
  end

  def to_pdf(dom, is_dark, layer_name)
    xml_str =  dom.to_s
    (is_dark ? $repl_dark : $repl_bright).each_pair{|k,v| xml_str.gsub!(k,v)}
    out_file = "../imgs/generated/"+(is_dark ? "dark_" : "bright_")+@outname+"_"+layer_name
    File.open(out_file+".svg","w"){|f| f.puts xml_str }
    system("inkscape", "-f",out_file+".svg", "-A", out_file+".pdf")
  end

  def generate_frame(dom,layer)
    puts "generating #{@outname}_#{layer}"
    generate_dom_frame(layer,dom)
    to_pdf(dom, true, layer);
    to_pdf(dom, false, layer);
  end

  def get_layers(dom)
    XPath.each(dom,"//svg/g[@inkscape:groupmode='layer']").map do |node|
      node.attributes["label"]
    end
  end

  def generate_dom_frame(layer,dom)
    XPath.each(dom,"//svg/g[@inkscape:groupmode='layer']") do |node|
      if layer == node.attributes["label"]
        node.attributes["style"]="display:visible"
      else
        node.attributes["style"]="display:none"
      end
    end
  end
end

class XCF2PNG < Generator
  def generate()
    system("xcf2png", @name,"-o", @outname+".png")
  end
end

def svg_anim(name,out)
  $anims << SvgAnim.new(name,out)
end

def xcf2png(name,out)
  $anims << XCF2PNG.new(name,out)
end

Dir.chdir(File.dirname(__FILE__))

Dir.glob("../imgs/*.svg").each do |file|
  svg_anim(file, File.basename(file, ".*"))
end

hashes = {}
$anims.each do |anim|
  anim.render
  hashes[anim.name+"|"+anim.outname] = anim.get_md5sum
end
File.open($path_to_hashes,"wb"){|f| f.print Marshal.dump(hashes)}
