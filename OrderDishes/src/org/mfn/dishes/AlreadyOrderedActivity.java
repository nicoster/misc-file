package org.mfn.dishes;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class AlreadyOrderedActivity extends ListActivity {

	private static class EfficientAdapter extends BaseAdapter {
		private LayoutInflater mInflater;
		private Bitmap mIcon1;
		private Bitmap mIcon2;

		public EfficientAdapter(Context context) {
			// Cache the LayoutInflate to avoid asking for a new one each time.
			mInflater = LayoutInflater.from(context);

			// Icons bound to the rows.
			mIcon1 = BitmapFactory.decodeResource(context.getResources(), R.drawable.icon48x48_1);
			mIcon2 = BitmapFactory.decodeResource(context.getResources(), R.drawable.icon48x48_2);
		}

		/**
		 * The number of items in the list is determined by the number of
		 * speeches in our array.
		 * 
		 * @see android.widget.ListAdapter#getCount()
		 */
		public int getCount() {
			return DATA.length;
		}

		/**
		 * Since the data comes from an array, just returning the index is
		 * sufficent to get at the data. If we were using a more complex data
		 * structure, we would return whatever object represents one row in the
		 * list.
		 * 
		 * @see android.widget.ListAdapter#getItem(int)
		 */
		public Object getItem(int position) {
			return position;
		}

		/**
		 * Use the array index as a unique id.
		 * 
		 * @see android.widget.ListAdapter#getItemId(int)
		 */
		public long getItemId(int position) {
			return position;
		}

		/**
		 * Make a view to hold each row.
		 * 
		 * @see android.widget.ListAdapter#getView(int, android.view.View,
		 *      android.view.ViewGroup)
		 */
		public View getView(int position, View convertView, ViewGroup parent) {
			// A ViewHolder keeps references to children views to avoid
			// unneccessary calls
			// to findViewById() on each row.
			ViewHolder holder;

			// When convertView is not null, we can reuse it directly, there is
			// no need
			// to reinflate it. We only inflate a new View when the convertView
			// supplied
			// by ListView is null.
			if (convertView == null) {
				convertView = mInflater.inflate(R.layout.list_item_icon_text, null);

				// Creates a ViewHolder and store references to the two children
				// views
				// we want to bind data to.
				holder = new ViewHolder();
				holder.text = (TextView) convertView.findViewById(R.id.text);
				holder.icon = (ImageView) convertView.findViewById(R.id.icon);

				convertView.setTag(holder);
			} else {
				// Get the ViewHolder back to get fast access to the TextView
				// and the ImageView.
				holder = (ViewHolder) convertView.getTag();
			}

			// Bind the data efficiently with the holder.
			holder.text.setText(DATA[position]);
			holder.icon.setImageBitmap((position & 1) == 1 ? mIcon1 : mIcon2);

			return convertView;
		}

		static class ViewHolder {
			TextView text;
			ImageView icon;
		}
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.already_order);

		setListAdapter(new EfficientAdapter(this));

//		Button b1 = (Button) findViewById(R.id.button1);
//
//		b1.setOnClickListener(new Button.OnClickListener() {
//			public void onClick(View v) {
//				Intent intent = new Intent();
//				intent.setClass(AlreadyOrderedActivity.this, AllDishesActivity.class);
//				startActivity(intent);
//
//			}
//		});
//		Button b2 = (Button) findViewById(R.id.button2);
//
//		b2.setOnClickListener(new Button.OnClickListener() {
//			public void onClick(View v) {
//				Intent intent = new Intent();
//				intent.setClass(AlreadyOrderedActivity.this, DishesTypeActivity.class);
//				startActivity(intent);
//
//			}
//		});
	}

	private static final String[] DATA = {"Abbaye de Belloc", "Abbaye du Mont des Cats", "Abertam", "Abondance",
			"Ackawi", "Acorn", "Adelost", "Affidelice au Chablis", "Afuega'l Pitu", "Airag", "Airedale", "Aisy Cendre",
			"Allgauer Emmentaler", "Alverca", "Ambert", "American Cheese", "Ami du Chambertin", "Anejo Enchilado",
			"Anneau du Vic-Bilh", "Anthoriro", "Appenzell", "Aragon", "Ardi Gasna", "Ardrahan", "Armenian String",
			"Aromes au Gene de Marc", "Asadero", "Asiago", "Aubisque Pyrenees", "Autun", "Avaxtskyr", "Baby Swiss",
			"Babybel", "Baguette Laonnaise", "Bakers", "Baladi", "Balaton", "Bandal", "Banon", "Barry's Bay Cheddar",
			"Basing", "Basket Cheese", "Bath Cheese", "Bavarian Bergkase", "Baylough", "Beaufort", "Beauvoorde",
			"Beenleigh Blue", "Beer Cheese", "Bel Paese", "Bergader", "Bergere Bleue", "Berkswell", "Beyaz Peynir",
			"Bierkase", "Bishop Kennedy", "Blarney"};
}
